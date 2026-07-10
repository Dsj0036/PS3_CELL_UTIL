#pragma once
#include "..\_ns.h"
#include "stream.h"
#include "..\array.h"
#include "..\array_param.h"
#include "..\allocator.h"
#include <sys/fs_external.h>

_SYS_NS
class memory_stream;

/**
 * @brief Internal implementation layer for memory_stream.
 *
 * The control block abstracts the storage behavior of a memory stream.
 * A memory stream can operate over:
 *
 * - Non-owning memory: references external memory without managing lifetime.
 * - Proprietary memory: owns the allocated buffer and controls its lifetime.
 *
 * This class is not intended to be directly exposed. memory_stream owns
 * an instance through a typed handle and delegates operations to it.
 */
namespace detail {

	typedef class memory_stream_control_block {

		friend sys::memory_stream;

	protected:

		/**
		 * @brief Indicates that the underlying storage allows write operations.
		 */
		static constexpr byte FLAG_WRITABLE = 1 << 2;

		/**
		 * @brief Indicates that the stream supports seeking.
		 */
		static constexpr byte FLAG_SEEKABLE = 1 << 3;

		/**
		 * @brief Indicates that the storage can dynamically resize.
		 */
		static constexpr byte FLAG_RESIZABLE = 1 << 4;


		/**
		 * @brief Describes the ownership model of the controlled memory.
		 */
		enum TypeFlags : int {

			/**
			 * @brief Undefined storage type.
			 */
			UNDEFINED,

			/**
			 * @brief Memory is externally owned and lifetime is managed elsewhere.
			 */
			NON_OWNING,

			/**
			 * @brief Memory is owned by this control block.
			 */
			PROPIETARY,
		};


		virtual TypeFlags getType() const;


		virtual bool is_writable() const;
		virtual bool is_seekable() const;


		/**
		 * @brief Performs the internal seek operation.
		 *
		 * @param offset Offset value.
		 * @param loc Seek origin.
		 */
		virtual bool _seek(int32_t offset, int32_t loc);


		bool seek(int32_t off, int dir);


		/**
		 * @brief Gets the beginning of the controlled memory.
		 */
		virtual const void* dta() const;
		virtual void* dta();


		/**
		 * @brief Gets the current cursor position pointer.
		 */
		virtual const uint8_t* cur() const;
		virtual uint8_t* cur();


		virtual void set_position(size_t position);
		virtual void set_length(size_t length);


		virtual size_t position() const;
		virtual size_t length() const;


		virtual void write(uchar b);
		virtual void write(uchar* dta, size_t length);


		virtual uchar read();
		virtual void read(uchar* data, size_t length);


		virtual ~memory_stream_control_block();


		class factory;

	} mscb;



	/**
	 * @brief Owning memory stream control block.
	 *
	 * This implementation allocates and manages its own internal storage.
	 * The lifetime of the memory buffer is tied to this control block.
	 */
	class mscb_propietary : public memory_stream_control_block {

		friend sys::memory_stream;
		friend mscb::factory;


		/**
		 * @brief Managed byte storage.
		 */
		sys::handle m_data;


		size_t m_capacity;
		size_t m_length;
		size_t m_position;


		/**
		 * @brief Internal state flags.
		 */
		byte m_flags;


	public:


		mscb_propietary(
			size_t capacity,
			bool resizable,
			sys::alloc* allocator
		);


		/**
		 * @brief Returns allocator used for the owned storage.
		 */
		inline sys::alloc* allocator() const {
			return m_data.allocator();
		}


		inline size_t capacity() const {
			return m_capacity;
		}


		inline bool resizable() const {
			return m_flags & FLAG_RESIZABLE;
		}



		virtual TypeFlags getType() const override;


		bool is_writable() const override;
		bool is_seekable() const override;


		void write(uchar b) override;
		void write(uchar* dta, size_t length) override;


		uchar read() override;
		void read(uchar* data, size_t length) override;


		void set_position(size_t position) override;
		void set_length(size_t length) override;


		size_t position() const override;
		size_t length() const override;



		/**
		 * @brief Releases ownership of the underlying memory.
		 *
		 * After this call this instance becomes invalid and no longer owns
		 * the memory block.
		 *
		 * The returned memory must be released using the same allocator
		 * that was originally used to allocate it.
		 *
		 * @return Raw pointer to the recovered memory block.
		 */
		unsigned char* pop();



		const void* dta() const override;
		void* dta() override;


		const uint8_t* cur() const override;
		uint8_t* cur() override;


		virtual ~mscb_propietary();


	private:


		void alloc(
			size_t capacity,
			sys::alloc* allocator,
			bool prev = false
		);


		void ensure_capacity(size_t len);
	};




	/**
	 * @brief Non-owning memory stream control block.
	 *
	 * References external memory without managing its lifetime.
	 * The caller is responsible for keeping the referenced buffer alive.
	 */
	class mscb_non_owning : public mscb {


		friend mscb::factory;


		uchar* m_data;

		size_t m_capacity;
		size_t m_length;
		size_t m_position;


		bool m_writable;


	public:


		mscb_non_owning(
			uchar* mdta,
			size_t cap,
			bool writable
		);



		TypeFlags getType() const override;


		size_t capacity() const;


		void write(uchar* dta, size_t length) override;
		void write(uchar c) override;


		uchar read() override;


		void read(uchar* data, size_t length) override;


		bool is_seekable() const override;


		bool is_writable() const override;


		void set_position(size_t position) override;
		void set_length(size_t position) override;


		size_t position() const override;
		size_t length() const override;


		const void* dta() const override;
		void* dta() override;


		const uint8_t* cur() const override;
		uint8_t* cur() override;


		virtual ~mscb_non_owning() = default;

	};




	/**
	 * @brief Factory responsible for creating memory stream implementations.
	 *
	 * Keeps construction details hidden from memory_stream and prevents
	 * exposing control block implementations publicly.
	 */
	class mscb::factory final {

	public:


		/**
		 * @brief Creates a non-owning memory stream backend.
		 */
		static void new_nonowning(
			sys::typed_handle<sys::detail::mscb>* target,
			uchar* in_data,
			size_t in_data_size,
			sys::alloc* setup_allocator,
			bool writable
		);



		/**
		 * @brief Creates an owning memory stream backend.
		 */
		static void new_owning(
			sys::typed_handle<sys::detail::mscb>* target,
			size_t capacity,
			sys::alloc* setup_allocator,
			bool resizable
		);

	};

}



/**
 * @brief Memory based stream implementation.
 *
 * Provides stream operations over a memory buffer.
 *
 * The actual storage management is delegated to an internal control block
 * implementation (`detail::mscb`), allowing the stream to operate over:
 *
 * - External memory (non-owning).
 * - Internally allocated memory (owning).
 *
 * The lifetime of the control block is managed internally through a typed handle.
 *
 * @note This class should not be allocated as a raw pointer unless its lifetime
 * is explicitly managed by an external owner.
 */
class memory_stream : public stream {


	/**
	 * @brief Internal storage manager.
	 *
	 * This should not be exposed.
	 * The stream delegates memory operations to this control block.
	 */
	sys::typed_handle<sys::detail::mscb> control_block{ nullptr };


public:


	/**
	 * @brief Creates an empty invalid memory stream.
	 *
	 * The stream does not contain an active backend until configured.
	 *
	 * @warning This instance must not be used until content is assigned.
	 */
	explicit memory_stream() : control_block(nullptr) {}


	/**
	 * @brief Memory streams cannot be copied.
	 */
	memory_stream(const memory_stream&) = delete;


	/**
	 * @brief Memory streams cannot be copy assigned.
	 */
	memory_stream& operator = (const memory_stream&) = delete;



	/**
	 * @brief Creates a non-owning memory stream.
	 *
	 * The provided buffer lifetime remains controlled externally.
	 *
	 * @param buffer External memory buffer.
	 * @param writable Enables write operations.
	 * @param allocator Allocator used for internal control structures.
	 */
	memory_stream(
		sys::array_param<uchar> buffer,
		bool writable,
		sys::alloc* allocator = sys::default_allocator
	);



	/**
	 * @brief Creates a non-owning memory stream from raw memory.
	 *
	 * @param buffer External memory pointer.
	 * @param buffer_size Available buffer capacity.
	 * @param writable Enables write operations.
	 */
	memory_stream(
		void* buffer,
		size_t buffer_size,
		bool writable,
		sys::alloc* allocator = sys::default_allocator
	);


	/**
	 * @brief Creates a non-owning stream with explicit current length.
	 *
	 * The capacity and the readable data length can differ.
	 */
	memory_stream(
		void* buffer,
		size_t buffer_size,
		size_t length,
		bool writable,
		sys::alloc* allocator = sys::default_allocator
	);


	/**
	 * @brief Creates an owning memory stream.
	 *
	 * Allocates internal storage controlled by the stream.
	 *
	 * @param capacity Initial storage capacity.
	 * @param resizable Enables dynamic expansion.
	 */
	memory_stream(
		size_t capacity,
		bool resizable,
		sys::alloc* allocator = sys::default_allocator
	);



	/**
	 * @brief Checks whether the stream has a valid backend.
	 */
	bool is_opened() const override;


	/**
	 * @brief Replaces the current content with an external memory source.
	 *
	 * Existing controlled data is released if present.
	 *
	 * The provided memory remains owned by the caller.
	 */
	void set_content_reader(
		void* inputBuffer,
		size_t bufferSize,
		size_t currentLength,
		bool writable,
		sys::alloc* allocator = sys::default_allocator
	);


	/**
	 * @brief Creates a readable external buffer using default settings.
	 */
	void set_content_reader(
		void* inputBuffer,
		size_t bufferSize
	);



	/**
	 * @brief Creates an owning memory backend.
	 *
	 * The stream becomes responsible for allocated storage lifetime.
	 */
	void set_content_owner(
		size_t capacity,
		sys::alloc* allocator,
		bool resizable
	);



	/**
	 * @brief Reads a single byte.
	 */
	virtual uchar read() override;



	/**
	 * @brief Writes raw data into the stream.
	 */
	virtual uint64_t write(
		const void* data,
		size_t count
	) override;



	/**
	 * @brief Reads raw data from the stream.
	 */
	virtual uint64_t read(
		void* buffer,
		size_t count
	) override;



	/**
	 * @brief Moves the stream cursor.
	 */
	virtual uint64_t seek(
		int64_t offset,
		int origin
	) override;



	/**
	 * @brief Gets total stream length.
	 */
	virtual uint64_t get_length() const override;



	/**
	 * @brief Gets current cursor position.
	 */
	virtual uint64_t get_position() const override;



	/**
	 * @brief Changes logical stream length.
	 */
	void set_length(size_t length);



	/**
	 * @brief Releases the controlled backend.
	 */
	virtual ~memory_stream();



	/**
	 * @brief Gets raw beginning address of the stream data.
	 */
	virtual uint8_t* dta() override;



	/**
	 * @brief Gets current cursor address.
	 */
	virtual uint8_t* cur() override;



protected:


	/**
	 * @brief Validates that the stream has an active backend.
	 *
	 * Throws when operations are performed on an uninitialized stream.
	 */
	void validatethis() const;

};

sys::typed_handle<sys::memory_stream> new_memory_stream(void* data, size_t length, sys::alloc* alloc);
sys::typed_handle<sys::memory_stream> new_memory_stream(void* data, size_t length);
_SYS_ENS