#pragma once
#include "System.h"
#include "include\vector.h"

namespace sys {

	struct FileStreamChunk {
		byte* chunk = nullptr;
		uint64_t start;
		int length;
	};
	class FileReader {

	public:
		static const int DEFAULT_CHUNK_SIZE = 256;
		static const int MAX_CHUNKS_IN_CACHE = 16; // puedes ajustar este valor
		FileReader() {
			this->_descriptor = 0;
			this->_chunkPos = 0;
			this->_readerChunkPos = 0;
			this->_rdposition = 0;
			this->_length = 0;
			
		}
	private:
		vector<FileStreamChunk> _cachedChunks; // for read.
		int _descriptor = 0;
		uint64_t _chunkPos = 0;
		uint64_t _length = 0;
		/* Reader */
		uint64_t _rdposition;
		FileStreamChunk* _readerChunk = nullptr;
		size_t _readerChunkPos = 0;

		int CacheNextChunk(int stem = 10, int min_size = 256) {
			FileStreamChunk chunk;
			chunk.length = static_cast<int>(MIN(_length / stem, min_size));
			chunk.chunk = (byte*)sys::memalign(16, chunk.length);
			chunk.start = _chunkPos;
			if (!chunk.chunk)
				return -1;
			uint64_t readed = 0;
			int result = cellFsRead(_descriptor, chunk.chunk, chunk.length, &readed);
			if (result < 0)
				return result;
			_chunkPos += readed;
			_cachedChunks.push_back(chunk);
			return 0;
		}

		void EvictOldestChunk() {
			if (!_cachedChunks.empty()) {
				FileStreamChunk& front = *_cachedChunks.begin();
				if (front.chunk)
					sys::free(front.chunk);
				_cachedChunks.remove_at(0);
			}
		}

		int CacheChunkAtPosition(uint64_t position, int chunkSize = DEFAULT_CHUNK_SIZE) {
			FileStreamChunk chunk;
			chunk.start = position;
			chunk.length = static_cast<int>(MIN(chunkSize, _length - position));
			chunk.chunk = (byte*)sys::memalign(16, chunk.length);
			if (!chunk.chunk)
				return -1;
			uint64_t _position;
			uint64_t readed = 0;
			int result = cellFsLseek(_descriptor, position, SEEK_SET, &_position);
			if (result < 0) return result;

			result = cellFsRead(_descriptor, chunk.chunk, chunk.length, &readed);
			if (result < 0) {
				sys::free(chunk.chunk);
				return result;
			}
			chunk.length = static_cast<int>(readed);
			_cachedChunks.push_back(chunk);

			// Evict if too many chunks cached
			if (_cachedChunks.size() > MAX_CHUNKS_IN_CACHE) {
				EvictOldestChunk();
			}
			return 0;
		}

		bool GetOrReadChunkForPosition(uint64_t position, FileStreamChunk*& outChunk, size_t& outLocalOffset, int chunkSize = DEFAULT_CHUNK_SIZE) {
			for (auto& chunk : _cachedChunks) {
				if (position >= chunk.start && position < chunk.start + chunk.length) {
					outChunk = &chunk;
					outLocalOffset = static_cast<size_t>(position - chunk.start);
					return true;
				}
			}

			// Not found in cache, load it
			int result = CacheChunkAtPosition(position, chunkSize);
			if (result != 0)
				return false;

			return GetOrReadChunkForPosition(position, outChunk, outLocalOffset, chunkSize);
		}

		int _EnsureGotBounds() {
			if (_readerChunk == nullptr || _rdposition < _readerChunk->start || _rdposition >= _readerChunk->start + _readerChunk->length) {
				return GetOrReadChunkForPosition(_rdposition, _readerChunk, _readerChunkPos, DEFAULT_CHUNK_SIZE);
				
			}
			_readerChunkPos = static_cast<size_t>(_rdposition - _readerChunk->start);
			return 0;
		}
	public:
		FileStreamChunk* GetChunkForPosition(uint64_t position) {
			uint64_t offset = 0;
			for (auto& chunk : _cachedChunks) {
				if (position >= offset && position < offset + chunk.length) {
					return &chunk;
				}
				offset += chunk.length;
			}
			return nullptr;
		}
		int seek(int origin, uint64_t offset) {
			switch (origin) {
			case SEEK_CUR:
				this->_rdposition = MIN(MAX(0, this->_rdposition + offset), this->_length);
				break;
			case SEEK_END:
				this->_rdposition = MIN(MAX(0, static_cast<int64_t>(_length) - static_cast<int64_t>(offset)), _length);
				break;
			case SEEK_SET:
				this->_rdposition = MIN(MAX(0, offset), _length);
				break;
			default:
				return 0;
			}
			_EnsureGotBounds();
			return 1;
		}

		
		inline bool isEOF() const { return _rdposition >=  _length-1; }
		inline const uint64_t& getOffset()const { return _rdposition; }
		inline const uint64_t& getLength() const { return _length; }
		int skip(int offset = 1)
		{
			if (!offset)
				return 0;

			int old = this->_rdposition;
			this->_rdposition = MIN(MAX(this->_rdposition + offset, 0), this->_length);
			return this->_rdposition - old;
		}
		bool canPeek(int size = 1) const {
			if (_rdposition > _length || !_readerChunk)
				return 0;
			return _descriptor != -1 && (_rdposition + size) < _length && _readerChunk->chunk;
		}
		int peekByte() const {
			if (!canPeek()) return -1;
			return _readerChunk->chunk[this->_readerChunkPos];
		}
		int32_t peekInt() const {
			if (!canPeek(4)) return -1;
			return *reinterpret_cast<int32_t*>(&_readerChunk->chunk[this->_readerChunkPos]);
		}
		uint32_t peekUInt() const {
			if (!canPeek(4)) return -1;
			return *reinterpret_cast<uint32_t*>(&_readerChunk->chunk[this->_readerChunkPos]);
		}
		int64_t peekInt64() const {
			if (!canPeek(8)) return -1;
			return *reinterpret_cast<int64_t*>(&_readerChunk->chunk[this->_readerChunkPos]);
		}
		uint64_t peekUInt64() const {
			if (!canPeek(8))return -1;
			return *reinterpret_cast<uint64_t*>(&_readerChunk->chunk[this->_readerChunkPos]);
		}
		int16_t peekInt16() const {
			if (!canPeek(2)) return -1;
			return *reinterpret_cast<int16_t*>(&_readerChunk->chunk[this->_readerChunkPos]);
		}
		uint16_t peekUInt16() const {
			if (!canPeek(2)) return -1;
			return *reinterpret_cast<int16_t*>(&_readerChunk->chunk[this->_readerChunkPos]);
		}
		double peekDouble() const {
			if (!canPeek(8)) return -1;
			return *reinterpret_cast<double*>(&_readerChunk->chunk[this->_readerChunkPos]);
		}
		float peekFloat() const {
			if (!canPeek(4)) return -1;
			return *reinterpret_cast<float*>(&_readerChunk->chunk[this->_readerChunkPos]);
		}
		int nextByte() {
			if (isEOF())
				return -1;

			int r = _EnsureGotBounds();
			if (r == 0) {
				int val = peekByte();
				_rdposition++;
				_readerChunkPos++;
				_EnsureGotBounds();

				return val;
			}
			return r;
		}
		int16_t nextInt16() {
			if (!canPeek(2)) return -1;
			int16_t val = peekInt16();
			_rdposition += 2;
			_EnsureGotBounds();
			return val;
		}

		uint16_t nextUInt16() {
			if (!canPeek(2)) return -1;
			uint16_t val = peekUInt16();
			_rdposition += 2;
			_EnsureGotBounds();
			return val;
		}

		int32_t nextInt() {
			if (!canPeek(4)) return -1;
			int32_t val = peekInt();
			_rdposition += 4;
			_EnsureGotBounds();
			return val;
		}

		uint32_t nextUInt() {
			if (!canPeek(4)) return -1;
			uint32_t val = peekUInt();
			_rdposition += 4;
			_EnsureGotBounds();
			return val;
		}

		int64_t nextInt64() {
			if (!canPeek(8)) return -1;
			int64_t val = peekInt64();
			_rdposition += 8;
			_EnsureGotBounds();
			return val;
		}

		uint64_t nextUInt64() {
			if (!canPeek(8)) return -1;
			uint64_t val = peekUInt64();
			_rdposition += 8;
			_EnsureGotBounds();
			return val;
		}

		float nextFloat() {
			if (!canPeek(4)) return -1;
			float val = peekFloat();
			_rdposition += 4;
			_EnsureGotBounds();
			return val;
		}

		double nextDouble() {
			if (!canPeek(8)) return -1;
			double val = peekDouble();
			_rdposition += 8;
			_EnsureGotBounds();
			return val;
		}

		int readLine(std::string& line) {
			line.clear();
			if (isEOF()) return 0;
			while (!isEOF()) {
				int c = nextByte();
				if (c == -1) break;

				if (c == '\n') {
					// Línea terminada con LF (Unix)
					break;
				}
				if (c == '\r') {
					// Podría ser CRLF (Windows) o CR (Mac antiguo)
					if (peekByte() == '\n') {
						nextByte(); // Consumir el '\n'
					}
					break;
				}
				line += static_cast<char>(c);
			}

			return !line.empty() ? 1 : 0;
		}


		inline int close() {
			if (this->_descriptor != -1)
			{

				for (auto& chunk : _cachedChunks) {
					if (chunk.chunk)
						sys::free(chunk.chunk);
				}
				_cachedChunks.clear();

				_length = 0;
				_rdposition = 0;
				_readerChunk = 0;
				cellFsClose(this->_descriptor);
				this->_descriptor = -1;
				return 0;
			}
			return -1;
		}

		int open(const char* path) {


			CellFsStat stat;
			int errn = cellFsStat(path, &stat);
			if (errn < 0)
				return errn;
			_length = stat.st_size;

			return cellFsOpenEx(path, CELL_FS_O_RDONLY, &this->_descriptor);
		}

		~FileReader() {
			for (auto& chunk : _cachedChunks) {
				if (chunk.chunk)
					sys::free(chunk.chunk);
			}
			_cachedChunks.clear();

			if (_descriptor >= 0) {
				cellFsClose(_descriptor);
				_descriptor = -1;
			}
		}

	};

}