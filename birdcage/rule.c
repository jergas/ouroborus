/* 0.9.7.2 on Thu Sep 25 19:21:11 2008 */

#define PY_SSIZE_T_CLEAN
#include "Python.h"
#include "structmember.h"
#ifndef PY_LONG_LONG
  #define PY_LONG_LONG LONG_LONG
#endif
#if PY_VERSION_HEX < 0x02050000
  typedef int Py_ssize_t;
  #define PY_SSIZE_T_MAX INT_MAX
  #define PY_SSIZE_T_MIN INT_MIN
  #define PyInt_FromSsize_t(z) PyInt_FromLong(z)
  #define PyInt_AsSsize_t(o)	PyInt_AsLong(o)
#endif
#ifndef WIN32
  #ifndef __stdcall
    #define __stdcall
  #endif
  #ifndef __cdecl
    #define __cdecl
  #endif
#endif
#ifdef __cplusplus
#define __PYX_EXTERN_C extern "C"
#else
#define __PYX_EXTERN_C extern
#endif
#include <math.h>


typedef struct {PyObject **p; char *s;} __Pyx_InternTabEntry; /*proto*/
typedef struct {PyObject **p; char *s; long n;} __Pyx_StringTabEntry; /*proto*/

static PyObject *__pyx_m;
static PyObject *__pyx_b;
static int __pyx_lineno;
static char *__pyx_filename;
static char **__pyx_f;

static int __Pyx_ArgTypeTest(PyObject *obj, PyTypeObject *type, int none_allowed, char *name); /*proto*/

static PyObject *__Pyx_Import(PyObject *name, PyObject *from_list); /*proto*/

static PyObject *__Pyx_GetName(PyObject *dict, PyObject *name); /*proto*/

static void __Pyx_Raise(PyObject *type, PyObject *value, PyObject *tb); /*proto*/

static PyObject *__Pyx_GetItemInt(PyObject *o, Py_ssize_t i); /*proto*/

static int __Pyx_InternStrings(__Pyx_InternTabEntry *t); /*proto*/

static int __Pyx_InitStrings(__Pyx_StringTabEntry *t); /*proto*/

static int __Pyx_SetVtable(PyObject *dict, void *vtable); /*proto*/

static PyTypeObject *__Pyx_ImportType(char *module_name, char *class_name, long size);  /*proto*/

static PyObject *__Pyx_ImportModule(char *name); /*proto*/

static int __Pyx_GetVtable(PyObject *dict, void *vtabptr); /*proto*/

static void __Pyx_AddTraceback(char *funcname); /*proto*/

/* Declarations from topology */

enum  {
  __pyx_e_8topology_caliber = 1000
};

struct __pyx_obj_8topology_Topology {
  PyObject_HEAD
  struct __pyx_vtabstruct_8topology_Topology *__pyx_vtab;
  int dimension;
  int background;
  int cells;
  PyObject *size;
  PyObject *zero;
  PyObject *name;
};

struct __pyx_obj_8topology_GridTopology {
  struct __pyx_obj_8topology_Topology __pyx_base;
  int border;
  int width;
  int height;
  int cell[__pyx_e_8topology_caliber][__pyx_e_8topology_caliber];
};

struct __pyx_obj_8topology_ToroidTopology {
  struct __pyx_obj_8topology_GridTopology __pyx_base;
};


struct __pyx_vtabstruct_8topology_Topology {
  int (*pyx_isNormalized)(struct __pyx_obj_8topology_Topology *,PyObject *);
  PyObject *(*pyx_normalize)(struct __pyx_obj_8topology_Topology *,PyObject *);
};
static struct __pyx_vtabstruct_8topology_Topology *__pyx_vtabptr_8topology_Topology;


struct __pyx_vtabstruct_8topology_GridTopology {
  struct __pyx_vtabstruct_8topology_Topology __pyx_base;
  int (*normal_x1)(struct __pyx_obj_8topology_GridTopology *,int);
  int (*normal_x2)(struct __pyx_obj_8topology_GridTopology *,int);
  int (*pyx_get)(struct __pyx_obj_8topology_GridTopology *,int,int);
  int (*pyx_get_nosafe)(struct __pyx_obj_8topology_GridTopology *,int,int);
  int (*pyx_set)(struct __pyx_obj_8topology_GridTopology *,int,int,int);
  void (*pyx_set_nosafe)(struct __pyx_obj_8topology_GridTopology *,int,int,int);
};
static struct __pyx_vtabstruct_8topology_GridTopology *__pyx_vtabptr_8topology_GridTopology;


struct __pyx_vtabstruct_8topology_ToroidTopology {
  struct __pyx_vtabstruct_8topology_GridTopology __pyx_base;
};
static struct __pyx_vtabstruct_8topology_ToroidTopology *__pyx_vtabptr_8topology_ToroidTopology;

static PyTypeObject *__pyx_ptype_8topology_Topology = 0;
static PyTypeObject *__pyx_ptype_8topology_GridTopology = 0;
static PyTypeObject *__pyx_ptype_8topology_ToroidTopology = 0;

/* Declarations from neighborhood */

enum  {
  __pyx_e_12neighborhood_capacity = 20
};

struct __pyx_obj_12neighborhood_Neighborhood_2D {
  PyObject_HEAD
  struct __pyx_vtabstruct_12neighborhood_Neighborhood_2D *__pyx_vtab;
  struct __pyx_obj_8topology_GridTopology *topology;
  int neighbors;
  PyObject *name;
  int neighbors_x1[__pyx_e_12neighborhood_capacity];
  int neighbors_x2[__pyx_e_12neighborhood_capacity];
  int neighbors_st[__pyx_e_12neighborhood_capacity];
};

struct __pyx_obj_12neighborhood_VonNeumannNeighborhood {
  struct __pyx_obj_12neighborhood_Neighborhood_2D __pyx_base;
};


struct __pyx_vtabstruct_12neighborhood_Neighborhood_2D {
  struct __pyx_obj_12neighborhood_Neighborhood_2D *(*pyx_clone)(struct __pyx_obj_12neighborhood_Neighborhood_2D *);
  void (*pyx_calculateNeighbors)(struct __pyx_obj_12neighborhood_Neighborhood_2D *,int,int);
  void (*pyx_calculateStates)(struct __pyx_obj_12neighborhood_Neighborhood_2D *,int,int);
  int (*pyx_reduceStates)(struct __pyx_obj_12neighborhood_Neighborhood_2D *,int,int,PyObject *,int);
  int (*pyx_sumStates)(struct __pyx_obj_12neighborhood_Neighborhood_2D *,int,int);
};
static struct __pyx_vtabstruct_12neighborhood_Neighborhood_2D *__pyx_vtabptr_12neighborhood_Neighborhood_2D;


struct __pyx_vtabstruct_12neighborhood_VonNeumannNeighborhood {
  struct __pyx_vtabstruct_12neighborhood_Neighborhood_2D __pyx_base;
};
static struct __pyx_vtabstruct_12neighborhood_VonNeumannNeighborhood *__pyx_vtabptr_12neighborhood_VonNeumannNeighborhood;

static PyTypeObject *__pyx_ptype_12neighborhood_Neighborhood_2D = 0;
static PyTypeObject *__pyx_ptype_12neighborhood_VonNeumannNeighborhood = 0;

/* Declarations from rule */

struct __pyx_obj_4rule_Rule_2D {
  PyObject_HEAD
  struct __pyx_vtabstruct_4rule_Rule_2D *__pyx_vtab;
  struct __pyx_obj_12neighborhood_Neighborhood_2D *neighborhood;
  PyObject *param;
  PyObject *name;
};

struct __pyx_obj_4rule_ReductionRule {
  struct __pyx_obj_4rule_Rule_2D __pyx_base;
};

struct __pyx_obj_4rule_ConwayRule {
  struct __pyx_obj_4rule_Rule_2D __pyx_base;
};


struct __pyx_vtabstruct_4rule_Rule_2D {
  PyObject *(*pyx_apply)(struct __pyx_obj_4rule_Rule_2D *,int,int);
  PyObject *(*pyx_applyToTarget)(struct __pyx_obj_4rule_Rule_2D *,int,int,struct __pyx_obj_8topology_GridTopology *);
};
static struct __pyx_vtabstruct_4rule_Rule_2D *__pyx_vtabptr_4rule_Rule_2D;


struct __pyx_vtabstruct_4rule_ReductionRule {
  struct __pyx_vtabstruct_4rule_Rule_2D __pyx_base;
};
static struct __pyx_vtabstruct_4rule_ReductionRule *__pyx_vtabptr_4rule_ReductionRule;


struct __pyx_vtabstruct_4rule_ConwayRule {
  struct __pyx_vtabstruct_4rule_Rule_2D __pyx_base;
};
static struct __pyx_vtabstruct_4rule_ConwayRule *__pyx_vtabptr_4rule_ConwayRule;

static PyTypeObject *__pyx_ptype_4rule_Rule_2D = 0;
static PyTypeObject *__pyx_ptype_4rule_ReductionRule = 0;
static PyTypeObject *__pyx_ptype_4rule_ConwayRule = 0;
static PyObject *__pyx_k2;
static PyObject *__pyx_k3;


/* Implementation of rule */


static PyObject *__pyx_n_exceptions_birdcage;
static PyObject *__pyx_n_E;

static PyObject *__pyx_k4p;

static char __pyx_k4[] = "Passive Rule 2-D";

static int __pyx_f_4rule_7Rule_2D___init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static int __pyx_f_4rule_7Rule_2D___init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  struct __pyx_obj_12neighborhood_Neighborhood_2D *__pyx_v_neighborhood = 0;
  PyObject *__pyx_v_param = 0;
  int __pyx_r;
  static char *__pyx_argnames[] = {"neighborhood","param",0};
  __pyx_v_param = __pyx_k2;
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "O|O", __pyx_argnames, &__pyx_v_neighborhood, &__pyx_v_param)) return -1;
  Py_INCREF(__pyx_v_self);
  Py_INCREF(__pyx_v_neighborhood);
  Py_INCREF(__pyx_v_param);
  if (!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_neighborhood), __pyx_ptype_12neighborhood_Neighborhood_2D, 1, "neighborhood")) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 36; goto __pyx_L1;}

  /* "/home/panx/ouroborus/birdcage/rule.pyx":43 */
  Py_INCREF(((PyObject *)__pyx_v_neighborhood));
  Py_DECREF(((PyObject *)((struct __pyx_obj_4rule_Rule_2D *)__pyx_v_self)->neighborhood));
  ((struct __pyx_obj_4rule_Rule_2D *)__pyx_v_self)->neighborhood = __pyx_v_neighborhood;

  /* "/home/panx/ouroborus/birdcage/rule.pyx":44 */
  Py_INCREF(__pyx_v_param);
  Py_DECREF(((struct __pyx_obj_4rule_Rule_2D *)__pyx_v_self)->param);
  ((struct __pyx_obj_4rule_Rule_2D *)__pyx_v_self)->param = __pyx_v_param;

  /* "/home/panx/ouroborus/birdcage/rule.pyx":45 */
  Py_INCREF(__pyx_k4p);
  Py_DECREF(((struct __pyx_obj_4rule_Rule_2D *)__pyx_v_self)->name);
  ((struct __pyx_obj_4rule_Rule_2D *)__pyx_v_self)->name = __pyx_k4p;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  __Pyx_AddTraceback("rule.Rule_2D.__init__");
  __pyx_r = -1;
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  Py_DECREF(__pyx_v_neighborhood);
  Py_DECREF(__pyx_v_param);
  return __pyx_r;
}

static PyObject *__pyx_f_4rule_7Rule_2D_handleNeighborhood(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_4rule_7Rule_2D_handleNeighborhood[] = "Return the associated neighborhood system for direct\n          manipulation from Python code\n\n          return -->> a birdcage Neighborhood_2D object";
static PyObject *__pyx_f_4rule_7Rule_2D_handleNeighborhood(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_r;
  static char *__pyx_argnames[] = {0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "", __pyx_argnames)) return 0;
  Py_INCREF(__pyx_v_self);
  Py_INCREF(((PyObject *)((struct __pyx_obj_4rule_Rule_2D *)__pyx_v_self)->neighborhood));
  __pyx_r = ((PyObject *)((struct __pyx_obj_4rule_Rule_2D *)__pyx_v_self)->neighborhood);
  goto __pyx_L0;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  return __pyx_r;
}

static PyObject *__pyx_n_InvalidAddressError;

static PyObject *__pyx_f_4rule_7Rule_2D_apply(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_4rule_7Rule_2D_apply[] = "Apply the state transition rule at a given address\n\n          address ---> a Python 2-tuple, the address of a cell in the grid\n          return  -->> None";
static PyObject *__pyx_f_4rule_7Rule_2D_apply(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_address = 0;
  PyObject *__pyx_r;
  Py_ssize_t __pyx_1;
  int __pyx_2;
  PyObject *__pyx_3 = 0;
  PyObject *__pyx_4 = 0;
  PyObject *__pyx_5 = 0;
  int __pyx_6;
  static char *__pyx_argnames[] = {"address",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "O", __pyx_argnames, &__pyx_v_address)) return 0;
  Py_INCREF(__pyx_v_self);
  Py_INCREF(__pyx_v_address);

  /* "/home/panx/ouroborus/birdcage/rule.pyx":63 */
  __pyx_1 = PyObject_Length(__pyx_v_address); if (__pyx_1 == -1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 63; goto __pyx_L1;}
  __pyx_2 = (!(__pyx_1 == 2));
  if (__pyx_2) {
    __pyx_3 = __Pyx_GetName(__pyx_m, __pyx_n_E); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 64; goto __pyx_L1;}
    __pyx_4 = PyObject_GetAttr(__pyx_3, __pyx_n_InvalidAddressError); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 64; goto __pyx_L1;}
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    __pyx_3 = PyTuple_New(2); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 64; goto __pyx_L1;}
    Py_INCREF(__pyx_v_address);
    PyTuple_SET_ITEM(__pyx_3, 0, __pyx_v_address);
    Py_INCREF(((struct __pyx_obj_4rule_Rule_2D *)__pyx_v_self)->neighborhood->topology->__pyx_base.name);
    PyTuple_SET_ITEM(__pyx_3, 1, ((struct __pyx_obj_4rule_Rule_2D *)__pyx_v_self)->neighborhood->topology->__pyx_base.name);
    __pyx_5 = PyObject_CallObject(__pyx_4, __pyx_3); if (!__pyx_5) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 64; goto __pyx_L1;}
    Py_DECREF(__pyx_4); __pyx_4 = 0;
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    __Pyx_Raise(__pyx_5, 0, 0);
    Py_DECREF(__pyx_5); __pyx_5 = 0;
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 64; goto __pyx_L1;}
    goto __pyx_L2;
  }
  __pyx_L2:;

  /* "/home/panx/ouroborus/birdcage/rule.pyx":66 */
  __pyx_4 = __Pyx_GetItemInt(__pyx_v_address, 0); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 66; goto __pyx_L1;}
  __pyx_2 = PyInt_AsLong(__pyx_4); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 66; goto __pyx_L1;}
  Py_DECREF(__pyx_4); __pyx_4 = 0;
  __pyx_3 = __Pyx_GetItemInt(__pyx_v_address, 1); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 66; goto __pyx_L1;}
  __pyx_6 = PyInt_AsLong(__pyx_3); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 66; goto __pyx_L1;}
  Py_DECREF(__pyx_3); __pyx_3 = 0;
  __pyx_5 = ((struct __pyx_vtabstruct_4rule_Rule_2D *)((struct __pyx_obj_4rule_Rule_2D *)__pyx_v_self)->__pyx_vtab)->pyx_apply(((struct __pyx_obj_4rule_Rule_2D *)__pyx_v_self),__pyx_2,__pyx_6); if (!__pyx_5) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 66; goto __pyx_L1;}
  Py_DECREF(__pyx_5); __pyx_5 = 0;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_3);
  Py_XDECREF(__pyx_4);
  Py_XDECREF(__pyx_5);
  __Pyx_AddTraceback("rule.Rule_2D.apply");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  Py_DECREF(__pyx_v_address);
  return __pyx_r;
}

static PyObject *__pyx_f_4rule_7Rule_2D_pyx_apply(struct __pyx_obj_4rule_Rule_2D *__pyx_v_self,int __pyx_v_x1,int __pyx_v_x2) {
  PyObject *__pyx_r;
  Py_INCREF(__pyx_v_self);

  __pyx_r = Py_None; Py_INCREF(Py_None);
  Py_DECREF(__pyx_v_self);
  return __pyx_r;
}

static PyObject *__pyx_f_4rule_7Rule_2D_applyToTarget(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_4rule_7Rule_2D_applyToTarget[] = "Apply the state transition rule at a given address in a\n          target cell grid different from the rule\'s own\n\n          address ---> a Python 2-tuple, the address of a cell in the grid\n          target ---> a birdcage GridTopology object such as a working\n                      grid in a synchronous automaton\n          return  -->> None";
static PyObject *__pyx_f_4rule_7Rule_2D_applyToTarget(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_address = 0;
  struct __pyx_obj_8topology_GridTopology *__pyx_v_target = 0;
  PyObject *__pyx_r;
  Py_ssize_t __pyx_1;
  int __pyx_2;
  PyObject *__pyx_3 = 0;
  PyObject *__pyx_4 = 0;
  PyObject *__pyx_5 = 0;
  int __pyx_6;
  static char *__pyx_argnames[] = {"address","target",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "OO", __pyx_argnames, &__pyx_v_address, &__pyx_v_target)) return 0;
  Py_INCREF(__pyx_v_self);
  Py_INCREF(__pyx_v_address);
  Py_INCREF((PyObject *)__pyx_v_target);
  if (!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_target), __pyx_ptype_8topology_GridTopology, 1, "target")) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 79; goto __pyx_L1;}

  /* "/home/panx/ouroborus/birdcage/rule.pyx":88 */
  __pyx_1 = PyObject_Length(__pyx_v_address); if (__pyx_1 == -1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 88; goto __pyx_L1;}
  __pyx_2 = (!(__pyx_1 == 2));
  if (__pyx_2) {
    __pyx_3 = __Pyx_GetName(__pyx_m, __pyx_n_E); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 89; goto __pyx_L1;}
    __pyx_4 = PyObject_GetAttr(__pyx_3, __pyx_n_InvalidAddressError); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 89; goto __pyx_L1;}
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    __pyx_3 = PyTuple_New(2); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 89; goto __pyx_L1;}
    Py_INCREF(__pyx_v_address);
    PyTuple_SET_ITEM(__pyx_3, 0, __pyx_v_address);
    Py_INCREF(((struct __pyx_obj_4rule_Rule_2D *)__pyx_v_self)->neighborhood->topology->__pyx_base.name);
    PyTuple_SET_ITEM(__pyx_3, 1, ((struct __pyx_obj_4rule_Rule_2D *)__pyx_v_self)->neighborhood->topology->__pyx_base.name);
    __pyx_5 = PyObject_CallObject(__pyx_4, __pyx_3); if (!__pyx_5) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 89; goto __pyx_L1;}
    Py_DECREF(__pyx_4); __pyx_4 = 0;
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    __Pyx_Raise(__pyx_5, 0, 0);
    Py_DECREF(__pyx_5); __pyx_5 = 0;
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 89; goto __pyx_L1;}
    goto __pyx_L2;
  }
  __pyx_L2:;

  /* "/home/panx/ouroborus/birdcage/rule.pyx":91 */
  __pyx_4 = __Pyx_GetItemInt(__pyx_v_address, 0); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 91; goto __pyx_L1;}
  __pyx_2 = PyInt_AsLong(__pyx_4); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 91; goto __pyx_L1;}
  Py_DECREF(__pyx_4); __pyx_4 = 0;
  __pyx_3 = __Pyx_GetItemInt(__pyx_v_address, 1); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 91; goto __pyx_L1;}
  __pyx_6 = PyInt_AsLong(__pyx_3); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 91; goto __pyx_L1;}
  Py_DECREF(__pyx_3); __pyx_3 = 0;
  __pyx_5 = ((struct __pyx_vtabstruct_4rule_Rule_2D *)((struct __pyx_obj_4rule_Rule_2D *)__pyx_v_self)->__pyx_vtab)->pyx_applyToTarget(((struct __pyx_obj_4rule_Rule_2D *)__pyx_v_self),__pyx_2,__pyx_6,__pyx_v_target); if (!__pyx_5) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 91; goto __pyx_L1;}
  Py_DECREF(__pyx_5); __pyx_5 = 0;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_3);
  Py_XDECREF(__pyx_4);
  Py_XDECREF(__pyx_5);
  __Pyx_AddTraceback("rule.Rule_2D.applyToTarget");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  Py_DECREF(__pyx_v_address);
  Py_DECREF((PyObject *)__pyx_v_target);
  return __pyx_r;
}

static PyObject *__pyx_f_4rule_7Rule_2D_pyx_applyToTarget(struct __pyx_obj_4rule_Rule_2D *__pyx_v_self,int __pyx_v_x1,int __pyx_v_x2,struct __pyx_obj_8topology_GridTopology *__pyx_v_target) {
  PyObject *__pyx_r;
  Py_INCREF(__pyx_v_self);
  Py_INCREF((PyObject *)__pyx_v_target);

  __pyx_r = Py_None; Py_INCREF(Py_None);
  Py_DECREF(__pyx_v_self);
  Py_DECREF((PyObject *)__pyx_v_target);
  return __pyx_r;
}

static PyObject *__pyx_n___init__;

static PyObject *__pyx_k5p;

static char __pyx_k5[] = "Reduction Rule";

static int __pyx_f_4rule_13ReductionRule___init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static int __pyx_f_4rule_13ReductionRule___init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  struct __pyx_obj_12neighborhood_Neighborhood_2D *__pyx_v_neighborhood = 0;
  PyObject *__pyx_v_param = 0;
  int __pyx_r;
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  static char *__pyx_argnames[] = {"neighborhood","param",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "OO", __pyx_argnames, &__pyx_v_neighborhood, &__pyx_v_param)) return -1;
  Py_INCREF((PyObject *)__pyx_v_self);
  Py_INCREF(__pyx_v_neighborhood);
  Py_INCREF(__pyx_v_param);
  if (!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_neighborhood), __pyx_ptype_12neighborhood_Neighborhood_2D, 1, "neighborhood")) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 115; goto __pyx_L1;}

  /* "/home/panx/ouroborus/birdcage/rule.pyx":123 */
  __pyx_1 = PyObject_GetAttr(((PyObject *)__pyx_ptype_4rule_Rule_2D), __pyx_n___init__); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 123; goto __pyx_L1;}
  __pyx_2 = PyTuple_New(3); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 123; goto __pyx_L1;}
  Py_INCREF(__pyx_v_self);
  PyTuple_SET_ITEM(__pyx_2, 0, __pyx_v_self);
  Py_INCREF(((PyObject *)__pyx_v_neighborhood));
  PyTuple_SET_ITEM(__pyx_2, 1, ((PyObject *)__pyx_v_neighborhood));
  Py_INCREF(__pyx_v_param);
  PyTuple_SET_ITEM(__pyx_2, 2, __pyx_v_param);
  __pyx_3 = PyObject_CallObject(__pyx_1, __pyx_2); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 123; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  Py_DECREF(__pyx_3); __pyx_3 = 0;

  /* "/home/panx/ouroborus/birdcage/rule.pyx":124 */
  Py_INCREF(__pyx_k5p);
  Py_DECREF(((struct __pyx_obj_4rule_ReductionRule *)__pyx_v_self)->__pyx_base.name);
  ((struct __pyx_obj_4rule_ReductionRule *)__pyx_v_self)->__pyx_base.name = __pyx_k5p;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  __Pyx_AddTraceback("rule.ReductionRule.__init__");
  __pyx_r = -1;
  __pyx_L0:;
  Py_DECREF((PyObject *)__pyx_v_self);
  Py_DECREF(__pyx_v_neighborhood);
  Py_DECREF(__pyx_v_param);
  return __pyx_r;
}

static PyObject *__pyx_f_4rule_13ReductionRule_pyx_apply(struct __pyx_obj_4rule_ReductionRule *__pyx_v_self,int __pyx_v_x1,int __pyx_v_x2) {
  int __pyx_v_state;
  PyObject *__pyx_r;
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  int __pyx_3;
  Py_INCREF((PyObject *)__pyx_v_self);

  /* "/home/panx/ouroborus/birdcage/rule.pyx":136 */
  __pyx_1 = __Pyx_GetItemInt(__pyx_v_self->__pyx_base.param, 0); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 136; goto __pyx_L1;}
  __pyx_2 = __Pyx_GetItemInt(__pyx_v_self->__pyx_base.param, 1); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 136; goto __pyx_L1;}
  __pyx_3 = PyInt_AsLong(__pyx_2); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 136; goto __pyx_L1;}
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  __pyx_v_state = ((struct __pyx_vtabstruct_12neighborhood_Neighborhood_2D *)__pyx_v_self->__pyx_base.neighborhood->__pyx_vtab)->pyx_reduceStates(__pyx_v_self->__pyx_base.neighborhood,__pyx_v_x1,__pyx_v_x2,__pyx_1,__pyx_3);
  Py_DECREF(__pyx_1); __pyx_1 = 0;

  /* "/home/panx/ouroborus/birdcage/rule.pyx":137 */
  ((struct __pyx_vtabstruct_8topology_GridTopology *)__pyx_v_self->__pyx_base.neighborhood->topology->__pyx_base.__pyx_vtab)->pyx_set(__pyx_v_self->__pyx_base.neighborhood->topology,__pyx_v_x1,__pyx_v_x2,__pyx_v_state);

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  __Pyx_AddTraceback("rule.ReductionRule.pyx_apply");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF((PyObject *)__pyx_v_self);
  return __pyx_r;
}

static PyObject *__pyx_f_4rule_13ReductionRule_pyx_applyToTarget(struct __pyx_obj_4rule_ReductionRule *__pyx_v_self,int __pyx_v_x1,int __pyx_v_x2,struct __pyx_obj_8topology_GridTopology *__pyx_v_target) {
  int __pyx_v_state;
  PyObject *__pyx_r;
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  int __pyx_3;
  Py_INCREF((PyObject *)__pyx_v_self);
  Py_INCREF((PyObject *)__pyx_v_target);

  /* "/home/panx/ouroborus/birdcage/rule.pyx":152 */
  __pyx_1 = __Pyx_GetItemInt(__pyx_v_self->__pyx_base.param, 0); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 152; goto __pyx_L1;}
  __pyx_2 = __Pyx_GetItemInt(__pyx_v_self->__pyx_base.param, 1); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 152; goto __pyx_L1;}
  __pyx_3 = PyInt_AsLong(__pyx_2); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 152; goto __pyx_L1;}
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  __pyx_v_state = ((struct __pyx_vtabstruct_12neighborhood_Neighborhood_2D *)__pyx_v_self->__pyx_base.neighborhood->__pyx_vtab)->pyx_reduceStates(__pyx_v_self->__pyx_base.neighborhood,__pyx_v_x1,__pyx_v_x2,__pyx_1,__pyx_3);
  Py_DECREF(__pyx_1); __pyx_1 = 0;

  /* "/home/panx/ouroborus/birdcage/rule.pyx":153 */
  ((struct __pyx_vtabstruct_8topology_GridTopology *)__pyx_v_target->__pyx_base.__pyx_vtab)->pyx_set(__pyx_v_target,__pyx_v_x1,__pyx_v_x2,__pyx_v_state);

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  __Pyx_AddTraceback("rule.ReductionRule.pyx_applyToTarget");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF((PyObject *)__pyx_v_self);
  Py_DECREF((PyObject *)__pyx_v_target);
  return __pyx_r;
}

static PyObject *__pyx_k6p;

static char __pyx_k6[] = "Conway Rule (3/2,3)";

static int __pyx_f_4rule_10ConwayRule___init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static int __pyx_f_4rule_10ConwayRule___init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  struct __pyx_obj_12neighborhood_Neighborhood_2D *__pyx_v_neighborhood = 0;
  PyObject *__pyx_v_param = 0;
  int __pyx_r;
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  static char *__pyx_argnames[] = {"neighborhood","param",0};
  __pyx_v_param = __pyx_k3;
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "O|O", __pyx_argnames, &__pyx_v_neighborhood, &__pyx_v_param)) return -1;
  Py_INCREF((PyObject *)__pyx_v_self);
  Py_INCREF(__pyx_v_neighborhood);
  Py_INCREF(__pyx_v_param);
  if (!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_neighborhood), __pyx_ptype_12neighborhood_Neighborhood_2D, 1, "neighborhood")) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 163; goto __pyx_L1;}

  /* "/home/panx/ouroborus/birdcage/rule.pyx":170 */
  __pyx_1 = PyObject_GetAttr(((PyObject *)__pyx_ptype_4rule_Rule_2D), __pyx_n___init__); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 170; goto __pyx_L1;}
  __pyx_2 = PyTuple_New(3); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 170; goto __pyx_L1;}
  Py_INCREF(__pyx_v_self);
  PyTuple_SET_ITEM(__pyx_2, 0, __pyx_v_self);
  Py_INCREF(((PyObject *)__pyx_v_neighborhood));
  PyTuple_SET_ITEM(__pyx_2, 1, ((PyObject *)__pyx_v_neighborhood));
  Py_INCREF(__pyx_v_param);
  PyTuple_SET_ITEM(__pyx_2, 2, __pyx_v_param);
  __pyx_3 = PyObject_CallObject(__pyx_1, __pyx_2); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 170; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  Py_DECREF(__pyx_3); __pyx_3 = 0;

  /* "/home/panx/ouroborus/birdcage/rule.pyx":171 */
  Py_INCREF(__pyx_k6p);
  Py_DECREF(((struct __pyx_obj_4rule_ConwayRule *)__pyx_v_self)->__pyx_base.name);
  ((struct __pyx_obj_4rule_ConwayRule *)__pyx_v_self)->__pyx_base.name = __pyx_k6p;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  __Pyx_AddTraceback("rule.ConwayRule.__init__");
  __pyx_r = -1;
  __pyx_L0:;
  Py_DECREF((PyObject *)__pyx_v_self);
  Py_DECREF(__pyx_v_neighborhood);
  Py_DECREF(__pyx_v_param);
  return __pyx_r;
}

static PyObject *__pyx_f_4rule_10ConwayRule_pyx_apply(struct __pyx_obj_4rule_ConwayRule *__pyx_v_self,int __pyx_v_x1,int __pyx_v_x2) {
  int __pyx_v_state;
  int __pyx_v_sumstates;
  int __pyx_v_cell;
  PyObject *__pyx_r;
  int __pyx_1;
  Py_INCREF((PyObject *)__pyx_v_self);

  /* "/home/panx/ouroborus/birdcage/rule.pyx":183 */
  __pyx_v_sumstates = ((struct __pyx_vtabstruct_12neighborhood_Neighborhood_2D *)__pyx_v_self->__pyx_base.neighborhood->__pyx_vtab)->pyx_sumStates(__pyx_v_self->__pyx_base.neighborhood,__pyx_v_x1,__pyx_v_x2);

  /* "/home/panx/ouroborus/birdcage/rule.pyx":184 */
  __pyx_v_cell = ((struct __pyx_vtabstruct_8topology_GridTopology *)__pyx_v_self->__pyx_base.neighborhood->topology->__pyx_base.__pyx_vtab)->pyx_get(__pyx_v_self->__pyx_base.neighborhood->topology,__pyx_v_x1,__pyx_v_x2);

  /* "/home/panx/ouroborus/birdcage/rule.pyx":185 */
  __pyx_1 = (__pyx_v_cell == 0);
  if (__pyx_1) {
    __pyx_1 = (__pyx_v_sumstates == 3);
  }
  if (__pyx_1) {
    __pyx_v_state = 1;
    goto __pyx_L2;
  }
  __pyx_1 = (__pyx_v_cell == 1);
  if (__pyx_1) {
    __pyx_1 = (__pyx_v_sumstates == 2);
  }
  if (!__pyx_1) {
    __pyx_1 = (__pyx_v_cell == 1);
    if (__pyx_1) {
      __pyx_1 = (__pyx_v_sumstates == 3);
    }
  }
  if (__pyx_1) {
    __pyx_v_state = 1;
    goto __pyx_L2;
  }
  /*else*/ {
    __pyx_v_state = 0;
  }
  __pyx_L2:;

  /* "/home/panx/ouroborus/birdcage/rule.pyx":192 */
  ((struct __pyx_vtabstruct_8topology_GridTopology *)__pyx_v_self->__pyx_base.neighborhood->topology->__pyx_base.__pyx_vtab)->pyx_set(__pyx_v_self->__pyx_base.neighborhood->topology,__pyx_v_x1,__pyx_v_x2,__pyx_v_state);

  __pyx_r = Py_None; Py_INCREF(Py_None);
  Py_DECREF((PyObject *)__pyx_v_self);
  return __pyx_r;
}

static PyObject *__pyx_f_4rule_10ConwayRule_pyx_applyToTarget(struct __pyx_obj_4rule_ConwayRule *__pyx_v_self,int __pyx_v_x1,int __pyx_v_x2,struct __pyx_obj_8topology_GridTopology *__pyx_v_target) {
  int __pyx_v_state;
  int __pyx_v_sumstates;
  int __pyx_v_cell;
  PyObject *__pyx_r;
  int __pyx_1;
  Py_INCREF((PyObject *)__pyx_v_self);
  Py_INCREF((PyObject *)__pyx_v_target);

  /* "/home/panx/ouroborus/birdcage/rule.pyx":207 */
  __pyx_v_sumstates = ((struct __pyx_vtabstruct_12neighborhood_Neighborhood_2D *)__pyx_v_self->__pyx_base.neighborhood->__pyx_vtab)->pyx_sumStates(__pyx_v_self->__pyx_base.neighborhood,__pyx_v_x1,__pyx_v_x2);

  /* "/home/panx/ouroborus/birdcage/rule.pyx":208 */
  __pyx_v_cell = ((struct __pyx_vtabstruct_8topology_GridTopology *)__pyx_v_self->__pyx_base.neighborhood->topology->__pyx_base.__pyx_vtab)->pyx_get(__pyx_v_self->__pyx_base.neighborhood->topology,__pyx_v_x1,__pyx_v_x2);

  /* "/home/panx/ouroborus/birdcage/rule.pyx":209 */
  __pyx_1 = (__pyx_v_cell == 0);
  if (__pyx_1) {
    __pyx_1 = (__pyx_v_sumstates == 3);
  }
  if (__pyx_1) {
    __pyx_v_state = 1;
    goto __pyx_L2;
  }
  __pyx_1 = (__pyx_v_cell == 1);
  if (__pyx_1) {
    __pyx_1 = (__pyx_v_sumstates == 2);
  }
  if (!__pyx_1) {
    __pyx_1 = (__pyx_v_cell == 1);
    if (__pyx_1) {
      __pyx_1 = (__pyx_v_sumstates == 3);
    }
  }
  if (__pyx_1) {
    __pyx_v_state = 1;
    goto __pyx_L2;
  }
  /*else*/ {
    __pyx_v_state = 0;
  }
  __pyx_L2:;

  /* "/home/panx/ouroborus/birdcage/rule.pyx":216 */
  ((struct __pyx_vtabstruct_8topology_GridTopology *)__pyx_v_target->__pyx_base.__pyx_vtab)->pyx_set(__pyx_v_target,__pyx_v_x1,__pyx_v_x2,__pyx_v_state);

  __pyx_r = Py_None; Py_INCREF(Py_None);
  Py_DECREF((PyObject *)__pyx_v_self);
  Py_DECREF((PyObject *)__pyx_v_target);
  return __pyx_r;
}

static __Pyx_InternTabEntry __pyx_intern_tab[] = {
  {&__pyx_n_E, "E"},
  {&__pyx_n_InvalidAddressError, "InvalidAddressError"},
  {&__pyx_n___init__, "__init__"},
  {&__pyx_n_exceptions_birdcage, "exceptions_birdcage"},
  {0, 0}
};

static __Pyx_StringTabEntry __pyx_string_tab[] = {
  {&__pyx_k4p, __pyx_k4, sizeof(__pyx_k4)},
  {&__pyx_k5p, __pyx_k5, sizeof(__pyx_k5)},
  {&__pyx_k6p, __pyx_k6, sizeof(__pyx_k6)},
  {0, 0, 0}
};
static struct __pyx_vtabstruct_4rule_Rule_2D __pyx_vtable_4rule_Rule_2D;

static PyObject *__pyx_tp_new_4rule_Rule_2D(PyTypeObject *t, PyObject *a, PyObject *k) {
  struct __pyx_obj_4rule_Rule_2D *p;
  PyObject *o = (*t->tp_alloc)(t, 0);
  if (!o) return 0;
  p = ((struct __pyx_obj_4rule_Rule_2D *)o);
  *(struct __pyx_vtabstruct_4rule_Rule_2D **)&p->__pyx_vtab = __pyx_vtabptr_4rule_Rule_2D;
  p->neighborhood = ((struct __pyx_obj_12neighborhood_Neighborhood_2D *)Py_None); Py_INCREF(Py_None);
  p->param = Py_None; Py_INCREF(Py_None);
  p->name = Py_None; Py_INCREF(Py_None);
  return o;
}

static void __pyx_tp_dealloc_4rule_Rule_2D(PyObject *o) {
  struct __pyx_obj_4rule_Rule_2D *p = (struct __pyx_obj_4rule_Rule_2D *)o;
  Py_XDECREF(((PyObject *)p->neighborhood));
  Py_XDECREF(p->param);
  Py_XDECREF(p->name);
  (*o->ob_type->tp_free)(o);
}

static int __pyx_tp_traverse_4rule_Rule_2D(PyObject *o, visitproc v, void *a) {
  int e;
  struct __pyx_obj_4rule_Rule_2D *p = (struct __pyx_obj_4rule_Rule_2D *)o;
  if (p->neighborhood) {
    e = (*v)(((PyObject*)p->neighborhood), a); if (e) return e;
  }
  if (p->param) {
    e = (*v)(p->param, a); if (e) return e;
  }
  if (p->name) {
    e = (*v)(p->name, a); if (e) return e;
  }
  return 0;
}

static int __pyx_tp_clear_4rule_Rule_2D(PyObject *o) {
  struct __pyx_obj_4rule_Rule_2D *p = (struct __pyx_obj_4rule_Rule_2D *)o;
  PyObject *t;
  t = ((PyObject *)p->neighborhood); 
  p->neighborhood = ((struct __pyx_obj_12neighborhood_Neighborhood_2D *)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(t);
  t = p->param; 
  p->param = Py_None; Py_INCREF(Py_None);
  Py_XDECREF(t);
  t = p->name; 
  p->name = Py_None; Py_INCREF(Py_None);
  Py_XDECREF(t);
  return 0;
}

static struct PyMethodDef __pyx_methods_4rule_Rule_2D[] = {
  {"handleNeighborhood", (PyCFunction)__pyx_f_4rule_7Rule_2D_handleNeighborhood, METH_VARARGS|METH_KEYWORDS, __pyx_doc_4rule_7Rule_2D_handleNeighborhood},
  {"apply", (PyCFunction)__pyx_f_4rule_7Rule_2D_apply, METH_VARARGS|METH_KEYWORDS, __pyx_doc_4rule_7Rule_2D_apply},
  {"applyToTarget", (PyCFunction)__pyx_f_4rule_7Rule_2D_applyToTarget, METH_VARARGS|METH_KEYWORDS, __pyx_doc_4rule_7Rule_2D_applyToTarget},
  {0, 0, 0, 0}
};

static PyNumberMethods __pyx_tp_as_number_Rule_2D = {
  0, /*nb_add*/
  0, /*nb_subtract*/
  0, /*nb_multiply*/
  0, /*nb_divide*/
  0, /*nb_remainder*/
  0, /*nb_divmod*/
  0, /*nb_power*/
  0, /*nb_negative*/
  0, /*nb_positive*/
  0, /*nb_absolute*/
  0, /*nb_nonzero*/
  0, /*nb_invert*/
  0, /*nb_lshift*/
  0, /*nb_rshift*/
  0, /*nb_and*/
  0, /*nb_xor*/
  0, /*nb_or*/
  0, /*nb_coerce*/
  0, /*nb_int*/
  0, /*nb_long*/
  0, /*nb_float*/
  0, /*nb_oct*/
  0, /*nb_hex*/
  0, /*nb_inplace_add*/
  0, /*nb_inplace_subtract*/
  0, /*nb_inplace_multiply*/
  0, /*nb_inplace_divide*/
  0, /*nb_inplace_remainder*/
  0, /*nb_inplace_power*/
  0, /*nb_inplace_lshift*/
  0, /*nb_inplace_rshift*/
  0, /*nb_inplace_and*/
  0, /*nb_inplace_xor*/
  0, /*nb_inplace_or*/
  0, /*nb_floor_divide*/
  0, /*nb_true_divide*/
  0, /*nb_inplace_floor_divide*/
  0, /*nb_inplace_true_divide*/
  #if Py_TPFLAGS_DEFAULT & Py_TPFLAGS_HAVE_INDEX
  0, /*nb_index*/
  #endif
};

static PySequenceMethods __pyx_tp_as_sequence_Rule_2D = {
  0, /*sq_length*/
  0, /*sq_concat*/
  0, /*sq_repeat*/
  0, /*sq_item*/
  0, /*sq_slice*/
  0, /*sq_ass_item*/
  0, /*sq_ass_slice*/
  0, /*sq_contains*/
  0, /*sq_inplace_concat*/
  0, /*sq_inplace_repeat*/
};

static PyMappingMethods __pyx_tp_as_mapping_Rule_2D = {
  0, /*mp_length*/
  0, /*mp_subscript*/
  0, /*mp_ass_subscript*/
};

static PyBufferProcs __pyx_tp_as_buffer_Rule_2D = {
  0, /*bf_getreadbuffer*/
  0, /*bf_getwritebuffer*/
  0, /*bf_getsegcount*/
  0, /*bf_getcharbuffer*/
};

PyTypeObject __pyx_type_4rule_Rule_2D = {
  PyObject_HEAD_INIT(0)
  0, /*ob_size*/
  "rule.Rule_2D", /*tp_name*/
  sizeof(struct __pyx_obj_4rule_Rule_2D), /*tp_basicsize*/
  0, /*tp_itemsize*/
  __pyx_tp_dealloc_4rule_Rule_2D, /*tp_dealloc*/
  0, /*tp_print*/
  0, /*tp_getattr*/
  0, /*tp_setattr*/
  0, /*tp_compare*/
  0, /*tp_repr*/
  &__pyx_tp_as_number_Rule_2D, /*tp_as_number*/
  &__pyx_tp_as_sequence_Rule_2D, /*tp_as_sequence*/
  &__pyx_tp_as_mapping_Rule_2D, /*tp_as_mapping*/
  0, /*tp_hash*/
  0, /*tp_call*/
  0, /*tp_str*/
  0, /*tp_getattro*/
  0, /*tp_setattro*/
  &__pyx_tp_as_buffer_Rule_2D, /*tp_as_buffer*/
  Py_TPFLAGS_DEFAULT|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_HAVE_GC, /*tp_flags*/
  "Abstract base class for all two-dimensional transition rules.\n     It actually does nothing at all.", /*tp_doc*/
  __pyx_tp_traverse_4rule_Rule_2D, /*tp_traverse*/
  __pyx_tp_clear_4rule_Rule_2D, /*tp_clear*/
  0, /*tp_richcompare*/
  0, /*tp_weaklistoffset*/
  0, /*tp_iter*/
  0, /*tp_iternext*/
  __pyx_methods_4rule_Rule_2D, /*tp_methods*/
  0, /*tp_members*/
  0, /*tp_getset*/
  0, /*tp_base*/
  0, /*tp_dict*/
  0, /*tp_descr_get*/
  0, /*tp_descr_set*/
  0, /*tp_dictoffset*/
  __pyx_f_4rule_7Rule_2D___init__, /*tp_init*/
  0, /*tp_alloc*/
  __pyx_tp_new_4rule_Rule_2D, /*tp_new*/
  0, /*tp_free*/
  0, /*tp_is_gc*/
  0, /*tp_bases*/
  0, /*tp_mro*/
  0, /*tp_cache*/
  0, /*tp_subclasses*/
  0, /*tp_weaklist*/
};
static struct __pyx_vtabstruct_4rule_ReductionRule __pyx_vtable_4rule_ReductionRule;

static PyObject *__pyx_tp_new_4rule_ReductionRule(PyTypeObject *t, PyObject *a, PyObject *k) {
  struct __pyx_obj_4rule_ReductionRule *p;
  PyObject *o = __pyx_ptype_4rule_Rule_2D->tp_new(t, a, k);
  if (!o) return 0;
  p = ((struct __pyx_obj_4rule_ReductionRule *)o);
  *(struct __pyx_vtabstruct_4rule_ReductionRule **)&p->__pyx_base.__pyx_vtab = __pyx_vtabptr_4rule_ReductionRule;
  return o;
}

static void __pyx_tp_dealloc_4rule_ReductionRule(PyObject *o) {
  __pyx_ptype_4rule_Rule_2D->tp_dealloc(o);
}

static struct PyMethodDef __pyx_methods_4rule_ReductionRule[] = {
  {0, 0, 0, 0}
};

static PyNumberMethods __pyx_tp_as_number_ReductionRule = {
  0, /*nb_add*/
  0, /*nb_subtract*/
  0, /*nb_multiply*/
  0, /*nb_divide*/
  0, /*nb_remainder*/
  0, /*nb_divmod*/
  0, /*nb_power*/
  0, /*nb_negative*/
  0, /*nb_positive*/
  0, /*nb_absolute*/
  0, /*nb_nonzero*/
  0, /*nb_invert*/
  0, /*nb_lshift*/
  0, /*nb_rshift*/
  0, /*nb_and*/
  0, /*nb_xor*/
  0, /*nb_or*/
  0, /*nb_coerce*/
  0, /*nb_int*/
  0, /*nb_long*/
  0, /*nb_float*/
  0, /*nb_oct*/
  0, /*nb_hex*/
  0, /*nb_inplace_add*/
  0, /*nb_inplace_subtract*/
  0, /*nb_inplace_multiply*/
  0, /*nb_inplace_divide*/
  0, /*nb_inplace_remainder*/
  0, /*nb_inplace_power*/
  0, /*nb_inplace_lshift*/
  0, /*nb_inplace_rshift*/
  0, /*nb_inplace_and*/
  0, /*nb_inplace_xor*/
  0, /*nb_inplace_or*/
  0, /*nb_floor_divide*/
  0, /*nb_true_divide*/
  0, /*nb_inplace_floor_divide*/
  0, /*nb_inplace_true_divide*/
  #if Py_TPFLAGS_DEFAULT & Py_TPFLAGS_HAVE_INDEX
  0, /*nb_index*/
  #endif
};

static PySequenceMethods __pyx_tp_as_sequence_ReductionRule = {
  0, /*sq_length*/
  0, /*sq_concat*/
  0, /*sq_repeat*/
  0, /*sq_item*/
  0, /*sq_slice*/
  0, /*sq_ass_item*/
  0, /*sq_ass_slice*/
  0, /*sq_contains*/
  0, /*sq_inplace_concat*/
  0, /*sq_inplace_repeat*/
};

static PyMappingMethods __pyx_tp_as_mapping_ReductionRule = {
  0, /*mp_length*/
  0, /*mp_subscript*/
  0, /*mp_ass_subscript*/
};

static PyBufferProcs __pyx_tp_as_buffer_ReductionRule = {
  0, /*bf_getreadbuffer*/
  0, /*bf_getwritebuffer*/
  0, /*bf_getsegcount*/
  0, /*bf_getcharbuffer*/
};

PyTypeObject __pyx_type_4rule_ReductionRule = {
  PyObject_HEAD_INIT(0)
  0, /*ob_size*/
  "rule.ReductionRule", /*tp_name*/
  sizeof(struct __pyx_obj_4rule_ReductionRule), /*tp_basicsize*/
  0, /*tp_itemsize*/
  __pyx_tp_dealloc_4rule_ReductionRule, /*tp_dealloc*/
  0, /*tp_print*/
  0, /*tp_getattr*/
  0, /*tp_setattr*/
  0, /*tp_compare*/
  0, /*tp_repr*/
  &__pyx_tp_as_number_ReductionRule, /*tp_as_number*/
  &__pyx_tp_as_sequence_ReductionRule, /*tp_as_sequence*/
  &__pyx_tp_as_mapping_ReductionRule, /*tp_as_mapping*/
  0, /*tp_hash*/
  0, /*tp_call*/
  0, /*tp_str*/
  0, /*tp_getattro*/
  0, /*tp_setattro*/
  &__pyx_tp_as_buffer_ReductionRule, /*tp_as_buffer*/
  Py_TPFLAGS_DEFAULT|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_BASETYPE, /*tp_flags*/
  "This rule applies a binary function recursively onto a cell\'s\n     neighbors", /*tp_doc*/
  0, /*tp_traverse*/
  0, /*tp_clear*/
  0, /*tp_richcompare*/
  0, /*tp_weaklistoffset*/
  0, /*tp_iter*/
  0, /*tp_iternext*/
  __pyx_methods_4rule_ReductionRule, /*tp_methods*/
  0, /*tp_members*/
  0, /*tp_getset*/
  0, /*tp_base*/
  0, /*tp_dict*/
  0, /*tp_descr_get*/
  0, /*tp_descr_set*/
  0, /*tp_dictoffset*/
  __pyx_f_4rule_13ReductionRule___init__, /*tp_init*/
  0, /*tp_alloc*/
  __pyx_tp_new_4rule_ReductionRule, /*tp_new*/
  0, /*tp_free*/
  0, /*tp_is_gc*/
  0, /*tp_bases*/
  0, /*tp_mro*/
  0, /*tp_cache*/
  0, /*tp_subclasses*/
  0, /*tp_weaklist*/
};
static struct __pyx_vtabstruct_4rule_ConwayRule __pyx_vtable_4rule_ConwayRule;

static PyObject *__pyx_tp_new_4rule_ConwayRule(PyTypeObject *t, PyObject *a, PyObject *k) {
  struct __pyx_obj_4rule_ConwayRule *p;
  PyObject *o = __pyx_ptype_4rule_Rule_2D->tp_new(t, a, k);
  if (!o) return 0;
  p = ((struct __pyx_obj_4rule_ConwayRule *)o);
  *(struct __pyx_vtabstruct_4rule_ConwayRule **)&p->__pyx_base.__pyx_vtab = __pyx_vtabptr_4rule_ConwayRule;
  return o;
}

static void __pyx_tp_dealloc_4rule_ConwayRule(PyObject *o) {
  __pyx_ptype_4rule_Rule_2D->tp_dealloc(o);
}

static struct PyMethodDef __pyx_methods_4rule_ConwayRule[] = {
  {0, 0, 0, 0}
};

static PyNumberMethods __pyx_tp_as_number_ConwayRule = {
  0, /*nb_add*/
  0, /*nb_subtract*/
  0, /*nb_multiply*/
  0, /*nb_divide*/
  0, /*nb_remainder*/
  0, /*nb_divmod*/
  0, /*nb_power*/
  0, /*nb_negative*/
  0, /*nb_positive*/
  0, /*nb_absolute*/
  0, /*nb_nonzero*/
  0, /*nb_invert*/
  0, /*nb_lshift*/
  0, /*nb_rshift*/
  0, /*nb_and*/
  0, /*nb_xor*/
  0, /*nb_or*/
  0, /*nb_coerce*/
  0, /*nb_int*/
  0, /*nb_long*/
  0, /*nb_float*/
  0, /*nb_oct*/
  0, /*nb_hex*/
  0, /*nb_inplace_add*/
  0, /*nb_inplace_subtract*/
  0, /*nb_inplace_multiply*/
  0, /*nb_inplace_divide*/
  0, /*nb_inplace_remainder*/
  0, /*nb_inplace_power*/
  0, /*nb_inplace_lshift*/
  0, /*nb_inplace_rshift*/
  0, /*nb_inplace_and*/
  0, /*nb_inplace_xor*/
  0, /*nb_inplace_or*/
  0, /*nb_floor_divide*/
  0, /*nb_true_divide*/
  0, /*nb_inplace_floor_divide*/
  0, /*nb_inplace_true_divide*/
  #if Py_TPFLAGS_DEFAULT & Py_TPFLAGS_HAVE_INDEX
  0, /*nb_index*/
  #endif
};

static PySequenceMethods __pyx_tp_as_sequence_ConwayRule = {
  0, /*sq_length*/
  0, /*sq_concat*/
  0, /*sq_repeat*/
  0, /*sq_item*/
  0, /*sq_slice*/
  0, /*sq_ass_item*/
  0, /*sq_ass_slice*/
  0, /*sq_contains*/
  0, /*sq_inplace_concat*/
  0, /*sq_inplace_repeat*/
};

static PyMappingMethods __pyx_tp_as_mapping_ConwayRule = {
  0, /*mp_length*/
  0, /*mp_subscript*/
  0, /*mp_ass_subscript*/
};

static PyBufferProcs __pyx_tp_as_buffer_ConwayRule = {
  0, /*bf_getreadbuffer*/
  0, /*bf_getwritebuffer*/
  0, /*bf_getsegcount*/
  0, /*bf_getcharbuffer*/
};

PyTypeObject __pyx_type_4rule_ConwayRule = {
  PyObject_HEAD_INIT(0)
  0, /*ob_size*/
  "rule.ConwayRule", /*tp_name*/
  sizeof(struct __pyx_obj_4rule_ConwayRule), /*tp_basicsize*/
  0, /*tp_itemsize*/
  __pyx_tp_dealloc_4rule_ConwayRule, /*tp_dealloc*/
  0, /*tp_print*/
  0, /*tp_getattr*/
  0, /*tp_setattr*/
  0, /*tp_compare*/
  0, /*tp_repr*/
  &__pyx_tp_as_number_ConwayRule, /*tp_as_number*/
  &__pyx_tp_as_sequence_ConwayRule, /*tp_as_sequence*/
  &__pyx_tp_as_mapping_ConwayRule, /*tp_as_mapping*/
  0, /*tp_hash*/
  0, /*tp_call*/
  0, /*tp_str*/
  0, /*tp_getattro*/
  0, /*tp_setattro*/
  &__pyx_tp_as_buffer_ConwayRule, /*tp_as_buffer*/
  Py_TPFLAGS_DEFAULT|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_BASETYPE, /*tp_flags*/
  "Conway\'s Game of Life rule. If the sum of a dead cell\'s neighbors\n     is 3, the cell becomes alive.  If the sum of a live cell\'s neighbors\n     is 2 or 3, the cell remains alive.  Otherwise, it dies.", /*tp_doc*/
  0, /*tp_traverse*/
  0, /*tp_clear*/
  0, /*tp_richcompare*/
  0, /*tp_weaklistoffset*/
  0, /*tp_iter*/
  0, /*tp_iternext*/
  __pyx_methods_4rule_ConwayRule, /*tp_methods*/
  0, /*tp_members*/
  0, /*tp_getset*/
  0, /*tp_base*/
  0, /*tp_dict*/
  0, /*tp_descr_get*/
  0, /*tp_descr_set*/
  0, /*tp_dictoffset*/
  __pyx_f_4rule_10ConwayRule___init__, /*tp_init*/
  0, /*tp_alloc*/
  __pyx_tp_new_4rule_ConwayRule, /*tp_new*/
  0, /*tp_free*/
  0, /*tp_is_gc*/
  0, /*tp_bases*/
  0, /*tp_mro*/
  0, /*tp_cache*/
  0, /*tp_subclasses*/
  0, /*tp_weaklist*/
};

static struct PyMethodDef __pyx_methods[] = {
  {0, 0, 0, 0}
};

static void __pyx_init_filenames(void); /*proto*/

PyMODINIT_FUNC initrule(void); /*proto*/
PyMODINIT_FUNC initrule(void) {
  PyObject *__pyx_1 = 0;
  __pyx_init_filenames();
  __pyx_m = Py_InitModule4("rule", __pyx_methods, 0, 0, PYTHON_API_VERSION);
  if (!__pyx_m) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 22; goto __pyx_L1;};
  Py_INCREF(__pyx_m);
  __pyx_b = PyImport_AddModule("__builtin__");
  if (!__pyx_b) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 22; goto __pyx_L1;};
  if (PyObject_SetAttrString(__pyx_m, "__builtins__", __pyx_b) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 22; goto __pyx_L1;};
  if (__Pyx_InternStrings(__pyx_intern_tab) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 22; goto __pyx_L1;};
  if (__Pyx_InitStrings(__pyx_string_tab) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 22; goto __pyx_L1;};
  __pyx_vtabptr_4rule_Rule_2D = &__pyx_vtable_4rule_Rule_2D;
  *(void(**)(void))&__pyx_vtable_4rule_Rule_2D.pyx_apply = (void(*)(void))__pyx_f_4rule_7Rule_2D_pyx_apply;
  *(void(**)(void))&__pyx_vtable_4rule_Rule_2D.pyx_applyToTarget = (void(*)(void))__pyx_f_4rule_7Rule_2D_pyx_applyToTarget;
  __pyx_type_4rule_Rule_2D.tp_free = _PyObject_GC_Del;
  if (PyType_Ready(&__pyx_type_4rule_Rule_2D) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 31; goto __pyx_L1;}
  if (__Pyx_SetVtable(__pyx_type_4rule_Rule_2D.tp_dict, __pyx_vtabptr_4rule_Rule_2D) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 31; goto __pyx_L1;}
  if (PyObject_SetAttrString(__pyx_m, "Rule_2D", (PyObject *)&__pyx_type_4rule_Rule_2D) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 31; goto __pyx_L1;}
  __pyx_ptype_4rule_Rule_2D = &__pyx_type_4rule_Rule_2D;
  __pyx_vtabptr_4rule_ReductionRule = &__pyx_vtable_4rule_ReductionRule;
  __pyx_vtable_4rule_ReductionRule.__pyx_base = *__pyx_vtabptr_4rule_Rule_2D;
  *(void(**)(void))&__pyx_vtable_4rule_ReductionRule.__pyx_base.pyx_apply = (void(*)(void))__pyx_f_4rule_13ReductionRule_pyx_apply;
  *(void(**)(void))&__pyx_vtable_4rule_ReductionRule.__pyx_base.pyx_applyToTarget = (void(*)(void))__pyx_f_4rule_13ReductionRule_pyx_applyToTarget;
  __pyx_type_4rule_ReductionRule.tp_base = __pyx_ptype_4rule_Rule_2D;
  if (PyType_Ready(&__pyx_type_4rule_ReductionRule) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 110; goto __pyx_L1;}
  if (__Pyx_SetVtable(__pyx_type_4rule_ReductionRule.tp_dict, __pyx_vtabptr_4rule_ReductionRule) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 110; goto __pyx_L1;}
  if (PyObject_SetAttrString(__pyx_m, "ReductionRule", (PyObject *)&__pyx_type_4rule_ReductionRule) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 110; goto __pyx_L1;}
  __pyx_ptype_4rule_ReductionRule = &__pyx_type_4rule_ReductionRule;
  __pyx_vtabptr_4rule_ConwayRule = &__pyx_vtable_4rule_ConwayRule;
  __pyx_vtable_4rule_ConwayRule.__pyx_base = *__pyx_vtabptr_4rule_Rule_2D;
  *(void(**)(void))&__pyx_vtable_4rule_ConwayRule.__pyx_base.pyx_apply = (void(*)(void))__pyx_f_4rule_10ConwayRule_pyx_apply;
  *(void(**)(void))&__pyx_vtable_4rule_ConwayRule.__pyx_base.pyx_applyToTarget = (void(*)(void))__pyx_f_4rule_10ConwayRule_pyx_applyToTarget;
  __pyx_type_4rule_ConwayRule.tp_base = __pyx_ptype_4rule_Rule_2D;
  if (PyType_Ready(&__pyx_type_4rule_ConwayRule) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 157; goto __pyx_L1;}
  if (__Pyx_SetVtable(__pyx_type_4rule_ConwayRule.tp_dict, __pyx_vtabptr_4rule_ConwayRule) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 157; goto __pyx_L1;}
  if (PyObject_SetAttrString(__pyx_m, "ConwayRule", (PyObject *)&__pyx_type_4rule_ConwayRule) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 157; goto __pyx_L1;}
  __pyx_ptype_4rule_ConwayRule = &__pyx_type_4rule_ConwayRule;
  __pyx_ptype_8topology_Topology = __Pyx_ImportType("topology", "Topology", sizeof(struct __pyx_obj_8topology_Topology)); if (!__pyx_ptype_8topology_Topology) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 13; goto __pyx_L1;}
  if (__Pyx_GetVtable(__pyx_ptype_8topology_Topology->tp_dict, &__pyx_vtabptr_8topology_Topology) < 0) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 13; goto __pyx_L1;}
  __pyx_ptype_8topology_GridTopology = __Pyx_ImportType("topology", "GridTopology", sizeof(struct __pyx_obj_8topology_GridTopology)); if (!__pyx_ptype_8topology_GridTopology) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 24; goto __pyx_L1;}
  if (__Pyx_GetVtable(__pyx_ptype_8topology_GridTopology->tp_dict, &__pyx_vtabptr_8topology_GridTopology) < 0) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 24; goto __pyx_L1;}
  __pyx_ptype_8topology_ToroidTopology = __Pyx_ImportType("topology", "ToroidTopology", sizeof(struct __pyx_obj_8topology_ToroidTopology)); if (!__pyx_ptype_8topology_ToroidTopology) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 44; goto __pyx_L1;}
  if (__Pyx_GetVtable(__pyx_ptype_8topology_ToroidTopology->tp_dict, &__pyx_vtabptr_8topology_ToroidTopology) < 0) {__pyx_filename = __pyx_f[1]; __pyx_lineno = 44; goto __pyx_L1;}
  __pyx_ptype_12neighborhood_Neighborhood_2D = __Pyx_ImportType("neighborhood", "Neighborhood_2D", sizeof(struct __pyx_obj_12neighborhood_Neighborhood_2D)); if (!__pyx_ptype_12neighborhood_Neighborhood_2D) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 21; goto __pyx_L1;}
  if (__Pyx_GetVtable(__pyx_ptype_12neighborhood_Neighborhood_2D->tp_dict, &__pyx_vtabptr_12neighborhood_Neighborhood_2D) < 0) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 21; goto __pyx_L1;}
  __pyx_ptype_12neighborhood_VonNeumannNeighborhood = __Pyx_ImportType("neighborhood", "VonNeumannNeighborhood", sizeof(struct __pyx_obj_12neighborhood_VonNeumannNeighborhood)); if (!__pyx_ptype_12neighborhood_VonNeumannNeighborhood) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 41; goto __pyx_L1;}
  if (__Pyx_GetVtable(__pyx_ptype_12neighborhood_VonNeumannNeighborhood->tp_dict, &__pyx_vtabptr_12neighborhood_VonNeumannNeighborhood) < 0) {__pyx_filename = __pyx_f[2]; __pyx_lineno = 41; goto __pyx_L1;}

  /* "/home/panx/ouroborus/birdcage/rule.pyx":22 */
  __pyx_1 = __Pyx_Import(__pyx_n_exceptions_birdcage, 0); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 22; goto __pyx_L1;}
  if (PyObject_SetAttr(__pyx_m, __pyx_n_E, __pyx_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 22; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;

  /* "/home/panx/ouroborus/birdcage/rule.pyx":36 */
  Py_INCREF(Py_None);
  __pyx_k2 = Py_None;

  /* "/home/panx/ouroborus/birdcage/rule.pyx":163 */
  Py_INCREF(Py_None);
  __pyx_k3 = Py_None;

  /* "/home/panx/ouroborus/birdcage/rule.pyx":195 */
  return;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  __Pyx_AddTraceback("rule");
}

static char *__pyx_filenames[] = {
  "rule.pyx",
  "topology.pxd",
  "neighborhood.pxd",
};

/* Runtime support code */

static void __pyx_init_filenames(void) {
  __pyx_f = __pyx_filenames;
}

static int __Pyx_ArgTypeTest(PyObject *obj, PyTypeObject *type, int none_allowed, char *name) {
    if (!type) {
        PyErr_Format(PyExc_SystemError, "Missing type object");
        return 0;
    }
    if ((none_allowed && obj == Py_None) || PyObject_TypeCheck(obj, type))
        return 1;
    PyErr_Format(PyExc_TypeError,
        "Argument '%s' has incorrect type (expected %s, got %s)",
        name, type->tp_name, obj->ob_type->tp_name);
    return 0;
}

static PyObject *__Pyx_Import(PyObject *name, PyObject *from_list) {
    PyObject *__import__ = 0;
    PyObject *empty_list = 0;
    PyObject *module = 0;
    PyObject *global_dict = 0;
    PyObject *empty_dict = 0;
    PyObject *list;
    __import__ = PyObject_GetAttrString(__pyx_b, "__import__");
    if (!__import__)
        goto bad;
    if (from_list)
        list = from_list;
    else {
        empty_list = PyList_New(0);
        if (!empty_list)
            goto bad;
        list = empty_list;
    }
    global_dict = PyModule_GetDict(__pyx_m);
    if (!global_dict)
        goto bad;
    empty_dict = PyDict_New();
    if (!empty_dict)
        goto bad;
    module = PyObject_CallFunction(__import__, "OOOO",
        name, global_dict, empty_dict, list);
bad:
    Py_XDECREF(empty_list);
    Py_XDECREF(__import__);
    Py_XDECREF(empty_dict);
    return module;
}

static PyObject *__Pyx_GetName(PyObject *dict, PyObject *name) {
    PyObject *result;
    result = PyObject_GetAttr(dict, name);
    if (!result)
        PyErr_SetObject(PyExc_NameError, name);
    return result;
}

static void __Pyx_Raise(PyObject *type, PyObject *value, PyObject *tb) {
    Py_XINCREF(type);
    Py_XINCREF(value);
    Py_XINCREF(tb);
    /* First, check the traceback argument, replacing None with NULL. */
    if (tb == Py_None) {
        Py_DECREF(tb);
        tb = 0;
    }
    else if (tb != NULL && !PyTraceBack_Check(tb)) {
        PyErr_SetString(PyExc_TypeError,
            "raise: arg 3 must be a traceback or None");
        goto raise_error;
    }
    /* Next, replace a missing value with None */
    if (value == NULL) {
        value = Py_None;
        Py_INCREF(value);
    }
    #if PY_VERSION_HEX < 0x02050000
    if (!PyClass_Check(type))
    #else
    if (!PyType_Check(type))
    #endif
    {
        /* Raising an instance.  The value should be a dummy. */
        if (value != Py_None) {
            PyErr_SetString(PyExc_TypeError,
                "instance exception may not have a separate value");
            goto raise_error;
        }
        /* Normalize to raise <class>, <instance> */
        Py_DECREF(value);
        value = type;
        #if PY_VERSION_HEX < 0x02050000
            if (PyInstance_Check(type)) {
                type = (PyObject*) ((PyInstanceObject*)type)->in_class;
                Py_INCREF(type);
            }
            else {
                PyErr_SetString(PyExc_TypeError,
                    "raise: exception must be an old-style class or instance");
                goto raise_error;
            }
        #else
            type = (PyObject*) type->ob_type;
            Py_INCREF(type);
            if (!PyType_IsSubtype((PyTypeObject *)type, (PyTypeObject *)PyExc_BaseException)) {
                PyErr_SetString(PyExc_TypeError,
                    "raise: exception class must be a subclass of BaseException");
                goto raise_error;
            }
        #endif
    }
    PyErr_Restore(type, value, tb);
    return;
raise_error:
    Py_XDECREF(value);
    Py_XDECREF(type);
    Py_XDECREF(tb);
    return;
}

static PyObject *__Pyx_GetItemInt(PyObject *o, Py_ssize_t i) {
    PyTypeObject *t = o->ob_type;
    PyObject *r;
    if (t->tp_as_sequence && t->tp_as_sequence->sq_item)
        r = PySequence_GetItem(o, i);
    else {
        PyObject *j = PyInt_FromLong(i);
        if (!j)
            return 0;
        r = PyObject_GetItem(o, j);
        Py_DECREF(j);
    }
    return r;
}

static int __Pyx_InternStrings(__Pyx_InternTabEntry *t) {
    while (t->p) {
        *t->p = PyString_InternFromString(t->s);
        if (!*t->p)
            return -1;
        ++t;
    }
    return 0;
}

static int __Pyx_InitStrings(__Pyx_StringTabEntry *t) {
    while (t->p) {
        *t->p = PyString_FromStringAndSize(t->s, t->n - 1);
        if (!*t->p)
            return -1;
        ++t;
    }
    return 0;
}

static int __Pyx_SetVtable(PyObject *dict, void *vtable) {
    PyObject *pycobj = 0;
    int result;
    
    pycobj = PyCObject_FromVoidPtr(vtable, 0);
    if (!pycobj)
        goto bad;
    if (PyDict_SetItemString(dict, "__pyx_vtable__", pycobj) < 0)
        goto bad;
    result = 0;
    goto done;

bad:
    result = -1;
done:
    Py_XDECREF(pycobj);
    return result;
}

#ifndef __PYX_HAVE_RT_ImportType
#define __PYX_HAVE_RT_ImportType
static PyTypeObject *__Pyx_ImportType(char *module_name, char *class_name, 
    long size) 
{
    PyObject *py_module = 0;
    PyObject *result = 0;
    
    py_module = __Pyx_ImportModule(module_name);
    if (!py_module)
        goto bad;
    result = PyObject_GetAttrString(py_module, class_name);
    if (!result)
        goto bad;
    if (!PyType_Check(result)) {
        PyErr_Format(PyExc_TypeError, 
            "%s.%s is not a type object",
            module_name, class_name);
        goto bad;
    }
    if (((PyTypeObject *)result)->tp_basicsize != size) {
        PyErr_Format(PyExc_ValueError, 
            "%s.%s does not appear to be the correct type object",
            module_name, class_name);
        goto bad;
    }
    return (PyTypeObject *)result;
bad:
    Py_XDECREF(result);
    return 0;
}
#endif

#ifndef __PYX_HAVE_RT_ImportModule
#define __PYX_HAVE_RT_ImportModule
static PyObject *__Pyx_ImportModule(char *name) {
    PyObject *py_name = 0;
    
    py_name = PyString_FromString(name);
    if (!py_name)
        goto bad;
    return PyImport_Import(py_name);
bad:
    Py_XDECREF(py_name);
    return 0;
}
#endif

static int __Pyx_GetVtable(PyObject *dict, void *vtabptr) {
    int result;
    PyObject *pycobj;
    
    pycobj = PyMapping_GetItemString(dict, "__pyx_vtable__");
    if (!pycobj)
        goto bad;
    *(void **)vtabptr = PyCObject_AsVoidPtr(pycobj);
    if (!*(void **)vtabptr)
        goto bad;
    result = 0;
    goto done;

bad:
    result = -1;
done:
    Py_XDECREF(pycobj);
    return result;
}

#include "compile.h"
#include "frameobject.h"
#include "traceback.h"

static void __Pyx_AddTraceback(char *funcname) {
    PyObject *py_srcfile = 0;
    PyObject *py_funcname = 0;
    PyObject *py_globals = 0;
    PyObject *empty_tuple = 0;
    PyObject *empty_string = 0;
    PyCodeObject *py_code = 0;
    PyFrameObject *py_frame = 0;
    
    py_srcfile = PyString_FromString(__pyx_filename);
    if (!py_srcfile) goto bad;
    py_funcname = PyString_FromString(funcname);
    if (!py_funcname) goto bad;
    py_globals = PyModule_GetDict(__pyx_m);
    if (!py_globals) goto bad;
    empty_tuple = PyTuple_New(0);
    if (!empty_tuple) goto bad;
    empty_string = PyString_FromString("");
    if (!empty_string) goto bad;
    py_code = PyCode_New(
        0,            /*int argcount,*/
        0,            /*int nlocals,*/
        0,            /*int stacksize,*/
        0,            /*int flags,*/
        empty_string, /*PyObject *code,*/
        empty_tuple,  /*PyObject *consts,*/
        empty_tuple,  /*PyObject *names,*/
        empty_tuple,  /*PyObject *varnames,*/
        empty_tuple,  /*PyObject *freevars,*/
        empty_tuple,  /*PyObject *cellvars,*/
        py_srcfile,   /*PyObject *filename,*/
        py_funcname,  /*PyObject *name,*/
        __pyx_lineno,   /*int firstlineno,*/
        empty_string  /*PyObject *lnotab*/
    );
    if (!py_code) goto bad;
    py_frame = PyFrame_New(
        PyThreadState_Get(), /*PyThreadState *tstate,*/
        py_code,             /*PyCodeObject *code,*/
        py_globals,          /*PyObject *globals,*/
        0                    /*PyObject *locals*/
    );
    if (!py_frame) goto bad;
    py_frame->f_lineno = __pyx_lineno;
    PyTraceBack_Here(py_frame);
bad:
    Py_XDECREF(py_srcfile);
    Py_XDECREF(py_funcname);
    Py_XDECREF(empty_tuple);
    Py_XDECREF(empty_string);
    Py_XDECREF(py_code);
    Py_XDECREF(py_frame);
}
