// Filename: findApproxPath.h
// Created by:  drose (18Feb00)
//
////////////////////////////////////////////////////////////////////

#ifndef FINDAPPROXPATH_H
#define FINDAPPROXPATH_H

#include <pandabase.h>

#include <typedObject.h>

#include <string>
#include <vector>

class Node;
class NodeRelation;

////////////////////////////////////////////////////////////////////
//       Class : FindApproxPath
// Description : This class is local to this package only; it doesn't
//               get exported.  It chops a string path, as supplied to
//               find_up() or find_down(), and breaks it up into its
//               component pieces.
////////////////////////////////////////////////////////////////////
class FindApproxPath {
public:
  INLINE FindApproxPath();

  bool add_string(const string &str_path);
  bool add_flags(const string &str_flags);
  bool add_component(string str_component);

  INLINE void add_match_name(const string &name, int flags);
  INLINE void add_match_name_glob(const string &glob, int flags);
  INLINE void add_match_exact_type(TypeHandle type, int flags);
  INLINE void add_match_inexact_type(TypeHandle type, int flags);
  INLINE void add_match_one(int flags);
  INLINE void add_match_many(int flags);
  INLINE void add_match_pointer(Node *pointer, int flags);

  INLINE int get_num_components() const;
  INLINE bool is_component_match_many(int index) const;
  INLINE bool matches_component(int index, NodeRelation *arc) const;
  INLINE bool matches_stashed(int index) const;

  INLINE bool return_hidden() const;
  INLINE bool return_stashed() const;

  void output(ostream &out) const;
  INLINE void output_component(ostream &out, int index) const;

#ifndef WIN32_VC
// Visual C++ won't let us define the ostream operator functions for
// these guys if they're private--even though we declare them friends.
private:
#endif
  enum ComponentType {
    CT_match_name,
    CT_match_name_glob,
    CT_match_exact_type,
    CT_match_inexact_type,
    CT_match_one,
    CT_match_many,
    CT_match_pointer
  };
  enum ComponentFlags {
    CF_stashed        = 0x001,
  };

  class Component {
  public:
    bool matches(NodeRelation *arc) const;
    void output(ostream &out) const;

    ComponentType _type;
    string _name;
    TypeHandle _type_handle;
    Node *_pointer;
    int _flags;
  };

  typedef vector<Component> Path;
  Path _path;

  bool _return_hidden;
  bool _return_stashed;

friend ostream &operator << (ostream &, FindApproxPath::ComponentType);
friend INLINE ostream &operator << (ostream &, const FindApproxPath::Component &);
};

ostream &
operator << (ostream &out, FindApproxPath::ComponentType type);

INLINE ostream &
operator << (ostream &out, const FindApproxPath::Component &component) {
  component.output(out);
  return out;
}

INLINE ostream &
operator << (ostream &out, const FindApproxPath &path) {
  path.output(out);
  return out;
}

#include "findApproxPath.I"

#endif
