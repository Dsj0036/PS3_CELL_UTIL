#pragma once
#include "BinaryReader.h"
#include "include\queue.h"
#include "Stack.h"
enum class JsonToken {
	None,
	StartObject,
	EndObject,
	StartArray,
	EndArray,
	Key,
	String,
	Number,
	Bool,
	Null,
	EndOfFile,
	Error
};

class JsonReader {
	BinaryReader reader;
	JsonToken currentToken;
	std::string currentKey;
	std::string currentValue;

public:
	JsonReader(const void* data, size_t length)
		: reader(data, length), currentToken(JsonToken::None) {
	}

	JsonToken GetToken() const { return currentToken; }
	const std::string& GetKey() const { return currentKey; }
	const std::string& GetValue() const { return currentValue; }

	int GetPosition()const {
		return reader.offset();
	}
	bool NextToken() {
		SkipWhitespace();

		if (reader.isEOF()) {
			currentToken = JsonToken::EndOfFile;
			return false;
		}

		char c = reader.Peek();

		switch (c) {
		case '{': reader.ReadUInt8(); currentToken = JsonToken::StartObject; return true;
		case '}': reader.ReadUInt8(); currentToken = JsonToken::EndObject; return true;
		case '[': reader.ReadUInt8(); currentToken = JsonToken::StartArray; return true;
		case ']': reader.ReadUInt8(); currentToken = JsonToken::EndArray; return true;
		case ',': reader.ReadUInt8(); return NextToken();
		case ':': reader.ReadUInt8(); return NextToken();
		case '"':
			currentValue = ReadString();
			currentToken = (currentToken == JsonToken::Key) ? JsonToken::String : JsonToken::Key;
			return true;
		case 't': case 'f': case 'n':
			currentValue = ReadLiteral();
			currentToken = (currentValue == "true" || currentValue == "false") ? JsonToken::Bool : JsonToken::Null;
			return true;
		default:
			if (IsDigit(c) || c == '-') {
				currentValue = ReadNumber();
				currentToken = JsonToken::Number;
				return true;
			}
			currentToken = JsonToken::Error;
			return false;
		}
	}

private:
	void SkipWhitespace() {
		while (!reader.isEOF()) {
			char c = reader.Peek();
			if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
				reader.ReadUInt8();
			}
			else {
				break;
			}
		}
	}

	std::string ReadString() {
		std::string result;
		reader.ReadUInt8(); // Skip initial "
		while (!reader.isEOF()) {
			char c = reader.ReadUInt8();
			if (c == '"') break;
			if (c == '\\') c = reader.ReadUInt8(); // Handle escape
			result.push_back(c);
		}
		return result;
	}

	std::string ReadLiteral() {
		std::string result;
		while (!reader.isEOF()) {
			char c = reader.Peek();
			if (!IsAlpha(c)) break;
			result.push_back(reader.ReadUInt8());
		}
		return result;
	}

	std::string ReadNumber() {
		std::string result;
		while (!reader.isEOF()) {
			char c = reader.Peek();
			if (!(IsDigit(c) || c == '.' || c == '-' || c == '+')) break;
			result.push_back(reader.ReadUInt8());
		}
		return result;
	}

	bool IsDigit(char c) const { return c >= '0' && c <= '9'; }
	bool IsAlpha(char c) const { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
};


class JsonValueCast; // partial caster declaration.

class JsonObject {
public:
	enum class Type {
		Null,
		Bool,
		Decimal,
		Text,
		Array,
		Object,
		RootObject,
	};

	System::Array<JsonObject>* descendants{ (System::Array<JsonObject>*) & NullDescendants };
	JsonObject* root;
	Type typeOf;
	std::string NameText;
	std::string ValueText;

	JsonObject() : typeOf(Type::Null), root(nullptr), descendants((System::Array<JsonObject>*)& NullDescendants) {}

	JsonObject(Type type, const std::string& key, const std::string& value)
		: typeOf(type), NameText(key), ValueText(value), root(nullptr), descendants((System::Array<JsonObject>*)& NullDescendants) {
	}
	JsonObject(const JsonObject& o) : typeOf(o.typeOf), NameText(o.NameText), descendants(o.descendants), root(o.root), ValueText(o.ValueText) {

	}

	class ParserManager {
		std::allocator<System::Array<JsonObject>> Allocator;
		System::Array<System::Array<JsonObject>*> Arrays;

	public:
		ParserManager() {}

		System::Array<JsonObject>* CreateNewArray() {
			System::Array<JsonObject>* newArray = Allocator.allocate(1);
			new (newArray) System::Array<JsonObject>(); // Coloca el objeto
			Arrays.Add(newArray);
			return newArray;
		}

		void HandleDestroy(JsonObject* const target) {
			if (target->isArray()) {
				Allocator.deallocate(target->descendants, 1);
			}
		}

		void SetArray(JsonObject* const target) {
			if (!target->isArray()) {
				target->descendants = CreateNewArray();
				target->typeOf = Type::Array;
			}
		}

		void AppendToArray(JsonObject* const array_object, const JsonObject& value) {
			if (array_object && array_object->isArray()) {
				array_object->descendants->Add(value);
			}
		}

		void AppendToArray(JsonObject* const array_object, JsonObject::Type type, const std::string& name, const std::string& value) {
			if (array_object && array_object->isArray()) {
				array_object->descendants->Add(JsonObject(type, name, value));
			}
		}

		void ResetTemplate(JsonObject& templateObject) {
			templateObject.NameText = "";
			templateObject.ValueText = "";
			templateObject.typeOf = Type::Null;
			templateObject.descendants = (System::Array<JsonObject>*) & NullDescendants;
			templateObject.root = nullptr;
		}

		System::Array<std::string> GetPath(const std::string& path) {
			BinaryReader reader(path.c_str(), path.length());
			string_stream builder;
			System::Array<std::string> result;

			while (!reader.isEOF()) {

				char c = reader.Peek();
				if (c == '.') {
					result.Add(builder.tostring());
					builder.clear();
					reader.ReadUInt8();
				}
				else
					builder << (char)reader.ReadUInt8();


			}
			result.Add(builder.tostring());
			return result;
		}

		ParserManager& operator=(ParserManager&) = delete;
		ParserManager& operator=(const ParserManager&) = delete;

		~ParserManager() {
			for (int i = Arrays.Count() - 1; i >= 0; i--) {
				Allocator.deallocate(Arrays[i], 1);
				Arrays.RemoveAt(i);
			}
		}
	};

	JsonObject& operator[](const std::string& str) {
		if (!isArray()) {
			return (JsonObject&)*&NullObject;
		}
		forIndexIn(descendants->Count()) {
			if ((*descendants)[i].NameText.compare(str) == 0) {
				return (*descendants)[i];
			}
		}
		return (JsonObject&)*&NullObject;
	}
	bool is(const JsonObject*& o) const {
		return this == o;
	}
	bool IsNull() const {
		return this->typeOf == Type::Null || this == &NullObject;
	}
	bool isArray() const {
		return descendants != &NullDescendants && descendants != nullptr;
	}
	JsonObject& operator[](size_t index) {
		if (isArray() && descendants) {
			if (descendants->Count() > 0)
				return descendants->operator[](index);
		}
		return (JsonObject&)*&NullObject;
	}
	JsonValueCast united();
	~JsonObject() {
		if (isArray()) {
			JsonParserManager.HandleDestroy(this);
		}
	}

	static ParserManager* const factoryGetParserManager() {
		return &JsonParserManager;
	}

	static const JsonObject NullObject;
private:
	static const System::Array<JsonObject> NullDescendants;
	static ParserManager JsonParserManager;
};

class JsonValueCast {
private:
	const JsonObject* origin;
public:
	JsonValueCast(const JsonObject& origin_) : origin(&origin_) {}
	static int default_int() { return 0; }
	static double default_double() { return 0.0; }
	static std::string default_string() { return EMPTY_STRING; }
	static bool default_boolean() { return false; }

	operator int() {
		if (!origin)
			return default_int();
		if (origin->typeOf != JsonObject::Type::Decimal)
			return default_int();
		return System::Int::Parse((char*)origin->ValueText.c_str());
	}
	operator double() {
		if (!origin)
			return default_double();
		if (origin->typeOf != JsonObject::Type::Decimal)
			return default_double();
		return System::Double::Parse((char*)origin->ValueText.c_str());
	}
	operator std::string() {
		if (!origin)
			return default_string();
		if (origin->typeOf != JsonObject::Type::Text)
			return default_string();
		return origin->ValueText;
	}
	explicit operator bool() {
		if (!origin)
			return default_boolean();
		if (origin->typeOf != JsonObject::Type::Bool)
			return default_boolean();
		return origin->ValueText == "true";

	}


};

JsonValueCast	JsonObject::united() {
	return JsonValueCast(*this);
}
#define log _sys_printf
const System::Array<JsonObject> JsonObject::NullDescendants{};
JsonObject::ParserManager JsonObject::JsonParserManager;
const JsonObject JsonObject::NullObject{};

class JsonDocument {
	friend JsonObject;

private:
	System::Array<JsonObject> Objects;

public:
	JsonDocument() {}

	JsonObject& const operator[](int32_t index) {
		return Objects[index];
	}

	JsonObject& const operator[](const std::string& key) {
		forIndexIn(Objects.Count()) {
			if (Objects[i].NameText.compare(key) == 0) {
				return Objects[i];
			}
		}
		return (JsonObject&)*&JsonObject::NullObject;
	}

	bool ContainsKey(const std::string& key) {
		forIndexIn(Objects.Count()) {
			if (Objects[i].NameText.compare(key) == 0) {
				return true;
			}
		}
		return false;
	}

	int32_t Count() const {
		return Objects.Count();
	}
	JsonObject& root() {
		return Objects[0];
	}
	JsonObject& href(const std::string& path) {
		System::Array<std::string> elems = JsonObject::factoryGetParserManager()->GetPath(path);
		JsonObject* current = nullptr;

		forIndexIn(elems.Count()) {
			if (!current) {
				if (System::Text::couldBeIntegerRepresentation(elems[i].c_str())) {
					int32_t index = System::Int::Parse((char*)elems[i].c_str());
					if (index > 0 && index < Objects.Count()) {
						current = &Objects[index];
						break;
					}
				}
				else {
					for (int j = 0; j < Objects.Count(); j++) {
						if (elems[i] == Objects[j].NameText) {
							current = &Objects[j];
							break;
						}
					}
				}
			}
			else {
				if (System::Text::couldBeIntegerRepresentation(elems[i].c_str())) {
					int32_t index = System::Int::Parse((char*)elems[i].c_str());
					if (index > 0 && index < current->descendants->Count()) {
						current = &current->descendants->operator[](index);
						break;
					}
				}
				else for (int j = 0; j < current->descendants->Count(); j++) {
					JsonObject& descendant = current->descendants->operator[](j);
					if (elems[i] == descendant.NameText) {
						current = &descendant;
						break;
					}
				}
			}
			if (!current)
				return (JsonObject&)JsonObject::NullObject;
		}
		return *current;
	}

	JsonObject::Type GetTypeForToken(JsonToken token) {
		switch (token) {
		case JsonToken::String: return JsonObject::Type::Text;
		case JsonToken::Number: return JsonObject::Type::Decimal;
		case JsonToken::Bool: return JsonObject::Type::Bool;
		case JsonToken::Null: return JsonObject::Type::Null;
		default: return JsonObject::Type::Object;
		}
	}

	void Parse(const std::string& doc) {
		JsonReader jreader(doc.c_str(), doc.length());
		JsonObject* currentParent = nullptr;
		JsonObject::ParserManager* parser = JsonObject::factoryGetParserManager();
		std::string current_key = EMPTY_STRING;


		while (jreader.NextToken()) {
			JsonToken token = jreader.GetToken();
			std::string value = jreader.GetValue();

			switch (token) {
			case JsonToken::StartObject: {
				JsonObject newObject(JsonObject::Type::Object, "", "");
				if (currentParent) {
					parser->AppendToArray(currentParent, newObject);
					currentParent->descendants->Last()->root = currentParent;
					currentParent = currentParent->descendants->Last();
				}
				else {
					Objects.Add(newObject);
					currentParent = Objects.Last();
				}
				break;
			}
			case JsonToken::EndObject: {
				if (currentParent && currentParent->root) {
					currentParent = currentParent->root;
				}
				else {
					currentParent = nullptr;
				}
				break;
			}
			case JsonToken::StartArray: {
				currentParent->typeOf = JsonObject::Type::Array;
				parser->SetArray(currentParent);
				break;
			}
			case JsonToken::EndArray: {
				if (currentParent && currentParent->root) {
					currentParent = currentParent->root;
				}
				break;
			}
			case JsonToken::Key: {
				if (currentParent) {
					currentParent->NameText = "[object]";
					current_key = jreader.GetValue();
				}
				break;
			}
			case JsonToken::String:
			case JsonToken::Number:
			case JsonToken::Bool:
			case JsonToken::Null: {
				if (currentParent) {
					if (!currentParent->isArray()) {
						parser->SetArray(currentParent);
					}
					JsonObject::Type type = GetTypeForToken(token);
					parser->AppendToArray(currentParent, type, current_key, jreader.GetValue());
				}
				break;
			}
			default:
				break;
			}
		}

		this->Objects[0].NameText = "root";

	}
};
