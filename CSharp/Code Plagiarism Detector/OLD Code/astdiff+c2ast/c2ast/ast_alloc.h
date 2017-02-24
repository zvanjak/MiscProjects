#ifndef _AST_ALLOC_
#define _AST_ALLOC_

#define AST_ALLOCATOR(AST_node_class) \
	AST_anode& AddNode(const AST_ncore &an) { \
		children.push_back(AST_node_class(an)); \
		vector<AST_node_class>::iterator nn = children.end()-1; \
		nn->parent = this; \
		return *nn; \
	} \
	\
	void ClearChildren() { \
		children.clear(); \
	} \
	\
	unsigned int GetNKids() const { \
		return children.size(); \
	} \
	\
	AST_node_class& operator [] (unsigned int id) { \
		return children[id]; \
	} \
	\
	const AST_node_class& operator [] (unsigned int id) const { \
		return children[id]; \
	} \
	\
	vector<AST_node_class> children;

#endif
