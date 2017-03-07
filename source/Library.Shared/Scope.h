#pragma once

#include "Datum.h"
#include "HashMap.h"
#include "RTTI.h"
#include "Vector.h"

namespace AnonymousEngine
{
	/** Scope is a collection of key value pairs. It also acts like a hierrarchical database
	 */
	class Scope : public RTTI
	{
	public:
		/** Default initialize a scope
		 */
		explicit Scope();

		/** Deep copy another scope and initialize a scope from that
		 *  @param rhs The scope to copy from
		 */
		Scope(const Scope& rhs);

		/** Deep copy and assign another scope into this
		 *  @param rhs The scope to copy from
		 *  @return The reference to the current scope
		 */
		Scope& operator=(const Scope& rhs);

		/** Move data from another scope and initialize a scope from that
		 *  @param rhs The scope to move from
		 */
		Scope(Scope&& rhs) noexcept;

		/** Mode and assign another scope into this
		 *  @param rhs The scope to move data from
		 *  @return The reference to the current scope
		 */
		Scope& operator=(Scope&& rhs) noexcept;

		/** Find a given key in the current scope
		 *  @param name The key to search for in the current scop
		 *  @return Address of the datum at that key. Returns nullptr if the key is not found
		 */
		Datum* Find(const std::string& name);

		/** Find a given key in the current scope. Constant version
		 *  @param name The key to search for in the current scop
		 *  @return Address of the datum at that key. Returns nullptr if the key is not found
		 */
		const Datum* Find(const std::string& name) const;

		/** Search for a key in the current scope. If not found in the current scope go up the
		 *  chain until The key is found
		 *  @param name The key to search for
		 *  @foundScope Output parameter to store the address of the scope in which the key was found.
		 */
		Datum* Search(const std::string& name, Scope** foundScope = nullptr);

		/** Search for a key in the current scope. If not found in the current scope go up the
		 *  chain until The key is found. Constant version
		 *  @param name The key to search for
		 *  @foundScope Output parameter to store the address of the scope in which the key was found.
		 */
		const Datum* Search(const std::string& name, Scope** foundScope = nullptr) const;

		/** Create a new Datum in the current scope at the given key. If the key exists already,
		 *		return the address of the existing Datum
		 *	DO NOT use this method for appending a scope. Use AppendScope instead.
		 *  @param name The key at which the Datum is to be created. 
		 *	@return A reference to the datum added / found at the given key
		 */
		Datum& Append(const std::string& name);

		/** Create a new Datum of type Scope at the given key. If the key exists, append a new scope to it.
		 *  If the already existing is of a different type an exception will be thrown
		 *  @param name The key at which the new scope is to be appended
		 *  @return A reference to the scope added
		 */
		Scope& AppendScope(const std::string& name);

		/** Adopt the given scope into the current scope. Set the current scope as the new scope's parent
		 *  Any association of this scope from the previous parent is removed
		 *  @param scope The reference to the scop which is to be adopted
		 *  @param name The name of the key under which the adopted scope should be added in this scope
		 */
		void Adopt(Scope& scope, const std::string& name);

		/** Get the address of the parent of the current scope
		 *  @return The address of the parent of the current scope
		 */
		const Scope* GetParent() const;

		/** Get a reference to the Datum at the given key in the current scope.
		 *  Works similar to Append, i.e. creates new Datum if no datum exists with the given key
		 *  @param name The key to search for
		 *  @return The address of the datum which was found / created
		 */
		Datum& operator[](const std::string& name);

		/** Get a reference to the Datum at the given key in the current scope.
		 *  Throws an exception if key was not found in the scope
		 *  @param name The key to search for
		 *  @return The address of the datum which was found
		 */
		const Datum& operator[](const std::string& name) const;

		/** Get the address of the Datum at the given index in the current scope.
		 *  Works similar to Append, i.e. creates new Datum if no datum exists with the given key
		 *  @param index The index to search for
		 *  @return The address of the datum which was found / created
		 */
		Datum& operator[](const std::uint32_t index);

		/** Get the address of the Datum at the given index in the current scope.
		 *  Throws an exception if key was not found in the scope
		 *  @param index The index to search for
		 *  @return The address of the datum which was found / created
		 */
		const Datum& operator[](const std::uint32_t index) const;

		/** Check if two scopes are logically equivalent
		 *  @param rhs The scope to compare the current scope to
		 *  @return Boolean indicating whether the two scopes are equal or not
		 */
		bool operator==(const Scope& rhs) const;

		/** Check if two scopes are logically inequivalent
		 *  @param rhs The scope to compare the current scope to
		 *  @return Boolean indicating whether the two scopes are unequal or not
		 */
		bool operator!=(const Scope& rhs) const;

		/** Virtual destructor for scope. Frees up all allocated child datums
		 */
		virtual ~Scope();

		/** Checks if this scope is logically equivalent to the passed in RTTI object.
		 *  The passed in object should also be a scope object for them to be equal
		 *  @param rhs The RTTI pointer to which this scope should be compared to
		 *  @return A boolean indicating whether this scope is equal to the passed in RTTI object or not
		 */
		bool Equals(const RTTI* rhs) const override;
		
		/** Generate a string representation of this scope
		 *  @return The string representation of this scope
		 */
		std::string ToString() const override;
		
		/** Set this scope's values from a passed in string
		 *  @param str The string to parse and read values from
		 */
		void FromString(const std::string& str) override;

		/** Clear all entries in the scope
		 */
		void Clear();

	protected:
		/** The child objects data map
		 */
		HashMap<std::string, Datum> mDatumMap;
		/** Ordered vector to store pointers to map entries in the order of insertion
		 */
		Vector<std::pair<const std::string, Datum>*> mOrderVector;

	private:
		// The pointer to the current scope's parent
		Scope* mParent;
		// Stores the key against which the parent has stored this scope
		std::string mParentKey;
		// Stores the index of this scope within the parent scope's datum where this is stored
		std::uint32_t mParentDatumIndex;

		// Copies another scope to this scope. Used by copy constructor and copy assignment operator
		void Copy(const Scope& rhs);
		// Moves another scope to this scope. Used by move constructor and move assignment operator
		void Move(Scope& rhs);
		// Detach the current scope from its parent
		void Orphan();

		RTTI_DECLARATIONS(Scope, RTTI)
	};
}
