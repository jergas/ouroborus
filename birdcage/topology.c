/* 0.9.7.2 on Thu Sep 25 19:21:07 2008 */

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

static PyObject *__Pyx_Import(PyObject *name, PyObject *from_list); /*proto*/

static PyObject *__Pyx_GetName(PyObject *dict, PyObject *name); /*proto*/

static void __Pyx_Raise(PyObject *type, PyObject *value, PyObject *tb); /*proto*/

static void __Pyx_WriteUnraisable(char *name); /*proto*/

static PyObject *__Pyx_UnpackItem(PyObject *); /*proto*/
static int __Pyx_EndUnpack(PyObject *); /*proto*/

static PyObject *__Pyx_GetItemInt(PyObject *o, Py_ssize_t i); /*proto*/

static int __Pyx_SetItemInt(PyObject *o, Py_ssize_t i, PyObject *v); /*proto*/

static int __Pyx_InternStrings(__Pyx_InternTabEntry *t); /*proto*/

static int __Pyx_InitStrings(__Pyx_StringTabEntry *t); /*proto*/

static int __Pyx_SetVtable(PyObject *dict, void *vtable); /*proto*/

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


/* Implementation of topology */


static PyObject *__pyx_n_exceptions_birdcage;
static PyObject *__pyx_n_E;
static PyObject *__pyx_n_operator;
static PyObject *__pyx_n_random;

static PyObject *__pyx_n_range;
static PyObject *__pyx_n_SizeError;
static PyObject *__pyx_n_reduce;
static PyObject *__pyx_n_mul;

static PyObject *__pyx_k4p;

static char __pyx_k4[] = "Abstract Topology";

static int __pyx_f_8topology_8Topology___init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static int __pyx_f_8topology_8Topology___init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_size = 0;
  int __pyx_v_background;
  PyObject *__pyx_v_i;
  int __pyx_r;
  Py_ssize_t __pyx_1;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  PyObject *__pyx_4 = 0;
  int __pyx_5;
  int __pyx_6;
  PyObject *__pyx_7 = 0;
  PyObject *__pyx_8 = 0;
  static char *__pyx_argnames[] = {"size","background",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "Oi", __pyx_argnames, &__pyx_v_size, &__pyx_v_background)) return -1;
  Py_INCREF(__pyx_v_self);
  Py_INCREF(__pyx_v_size);
  __pyx_v_i = Py_None; Py_INCREF(Py_None);

  /* "/home/panx/ouroborus/birdcage/topology.pyx":46 */
  ((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->background = __pyx_v_background;

  /* "/home/panx/ouroborus/birdcage/topology.pyx":47 */
  Py_INCREF(__pyx_v_size);
  Py_DECREF(((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->size);
  ((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->size = __pyx_v_size;

  /* "/home/panx/ouroborus/birdcage/topology.pyx":48 */
  __pyx_1 = PyObject_Length(((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->size); if (__pyx_1 == -1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 48; goto __pyx_L1;}
  ((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->dimension = __pyx_1;

  /* "/home/panx/ouroborus/birdcage/topology.pyx":49 */
  Py_INCREF(__pyx_k4p);
  Py_DECREF(((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->name);
  ((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->name = __pyx_k4p;

  /* "/home/panx/ouroborus/birdcage/topology.pyx":52 */
  __pyx_2 = __Pyx_GetName(__pyx_b, __pyx_n_range); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 52; goto __pyx_L1;}
  __pyx_3 = PyInt_FromLong(((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->dimension); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 52; goto __pyx_L1;}
  __pyx_4 = PyTuple_New(1); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 52; goto __pyx_L1;}
  PyTuple_SET_ITEM(__pyx_4, 0, __pyx_3);
  __pyx_3 = 0;
  __pyx_3 = PyObject_CallObject(__pyx_2, __pyx_4); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 52; goto __pyx_L1;}
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  Py_DECREF(__pyx_4); __pyx_4 = 0;
  __pyx_2 = PyObject_GetIter(__pyx_3); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 52; goto __pyx_L1;}
  Py_DECREF(__pyx_3); __pyx_3 = 0;
  for (;;) {
    __pyx_4 = PyIter_Next(__pyx_2);
    if (!__pyx_4) {
      if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 52; goto __pyx_L1;}
      break;
    }
    Py_DECREF(__pyx_v_i);
    __pyx_v_i = __pyx_4;
    __pyx_4 = 0;
    __pyx_3 = PyObject_GetItem(__pyx_v_size, __pyx_v_i); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 53; goto __pyx_L1;}
    __pyx_4 = PyInt_FromLong(__pyx_e_8topology_caliber); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 53; goto __pyx_L1;}
    if (PyObject_Cmp(__pyx_3, __pyx_4, &__pyx_5) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 53; goto __pyx_L1;}
    __pyx_5 = __pyx_5 < 0;
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    Py_DECREF(__pyx_4); __pyx_4 = 0;
    __pyx_6 = (!__pyx_5);
    if (__pyx_6) {
      __pyx_3 = __Pyx_GetName(__pyx_m, __pyx_n_E); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 54; goto __pyx_L1;}
      __pyx_4 = PyObject_GetAttr(__pyx_3, __pyx_n_SizeError); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 54; goto __pyx_L1;}
      Py_DECREF(__pyx_3); __pyx_3 = 0;
      __pyx_3 = PyObject_GetItem(__pyx_v_size, __pyx_v_i); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 54; goto __pyx_L1;}
      __pyx_7 = PyInt_FromLong(__pyx_e_8topology_caliber); if (!__pyx_7) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 54; goto __pyx_L1;}
      __pyx_8 = PyTuple_New(2); if (!__pyx_8) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 54; goto __pyx_L1;}
      PyTuple_SET_ITEM(__pyx_8, 0, __pyx_3);
      PyTuple_SET_ITEM(__pyx_8, 1, __pyx_7);
      __pyx_3 = 0;
      __pyx_7 = 0;
      __pyx_3 = PyObject_CallObject(__pyx_4, __pyx_8); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 54; goto __pyx_L1;}
      Py_DECREF(__pyx_4); __pyx_4 = 0;
      Py_DECREF(__pyx_8); __pyx_8 = 0;
      __Pyx_Raise(__pyx_3, 0, 0);
      Py_DECREF(__pyx_3); __pyx_3 = 0;
      {__pyx_filename = __pyx_f[0]; __pyx_lineno = 54; goto __pyx_L1;}
      goto __pyx_L4;
    }
    __pyx_L4:;
  }
  Py_DECREF(__pyx_2); __pyx_2 = 0;

  /* "/home/panx/ouroborus/birdcage/topology.pyx":58 */
  __pyx_7 = __Pyx_GetName(__pyx_b, __pyx_n_reduce); if (!__pyx_7) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 58; goto __pyx_L1;}
  __pyx_4 = __Pyx_GetName(__pyx_m, __pyx_n_operator); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 58; goto __pyx_L1;}
  __pyx_8 = PyObject_GetAttr(__pyx_4, __pyx_n_mul); if (!__pyx_8) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 58; goto __pyx_L1;}
  Py_DECREF(__pyx_4); __pyx_4 = 0;
  __pyx_3 = PyInt_FromLong(1); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 58; goto __pyx_L1;}
  __pyx_2 = PyTuple_New(3); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 58; goto __pyx_L1;}
  PyTuple_SET_ITEM(__pyx_2, 0, __pyx_8);
  Py_INCREF(((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->size);
  PyTuple_SET_ITEM(__pyx_2, 1, ((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->size);
  PyTuple_SET_ITEM(__pyx_2, 2, __pyx_3);
  __pyx_8 = 0;
  __pyx_3 = 0;
  __pyx_4 = PyObject_CallObject(__pyx_7, __pyx_2); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 58; goto __pyx_L1;}
  Py_DECREF(__pyx_7); __pyx_7 = 0;
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  __pyx_5 = PyInt_AsLong(__pyx_4); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 58; goto __pyx_L1;}
  Py_DECREF(__pyx_4); __pyx_4 = 0;
  ((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->cells = __pyx_5;

  /* "/home/panx/ouroborus/birdcage/topology.pyx":61 */
  __pyx_8 = PyInt_FromLong(0); if (!__pyx_8) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 61; goto __pyx_L1;}
  __pyx_3 = PyTuple_New(1); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 61; goto __pyx_L1;}
  PyTuple_SET_ITEM(__pyx_3, 0, __pyx_8);
  __pyx_8 = 0;
  __pyx_7 = PyInt_FromLong(((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->dimension); if (!__pyx_7) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 61; goto __pyx_L1;}
  __pyx_2 = PyNumber_Multiply(__pyx_3, __pyx_7); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 61; goto __pyx_L1;}
  Py_DECREF(__pyx_3); __pyx_3 = 0;
  Py_DECREF(__pyx_7); __pyx_7 = 0;
  Py_DECREF(((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->zero);
  ((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->zero = __pyx_2;
  __pyx_2 = 0;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  Py_XDECREF(__pyx_4);
  Py_XDECREF(__pyx_7);
  Py_XDECREF(__pyx_8);
  __Pyx_AddTraceback("topology.Topology.__init__");
  __pyx_r = -1;
  __pyx_L0:;
  Py_DECREF(__pyx_v_i);
  Py_DECREF(__pyx_v_self);
  Py_DECREF(__pyx_v_size);
  return __pyx_r;
}

static PyObject *__pyx_n_InvalidAddressError;

static PyObject *__pyx_f_8topology_8Topology_isNormalized(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_8topology_8Topology_isNormalized[] = "Check whether a cell\'s address is normalised\n\n          address ---> a grid coordinate value in the form of a Python n-tuple\n          return  -->> True if address is normalised, False otherwise";
static PyObject *__pyx_f_8topology_8Topology_isNormalized(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_address = 0;
  PyObject *__pyx_r;
  int __pyx_1;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  PyObject *__pyx_4 = 0;
  static char *__pyx_argnames[] = {"address",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "O", __pyx_argnames, &__pyx_v_address)) return 0;
  Py_INCREF(__pyx_v_self);
  Py_INCREF(__pyx_v_address);
  __pyx_1 = (((struct __pyx_vtabstruct_8topology_Topology *)((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->__pyx_vtab)->pyx_isNormalized(((struct __pyx_obj_8topology_Topology *)__pyx_v_self),__pyx_v_address) == (-1));
  if (__pyx_1) {
    __pyx_2 = __Pyx_GetName(__pyx_m, __pyx_n_E); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 71; goto __pyx_L1;}
    __pyx_3 = PyObject_GetAttr(__pyx_2, __pyx_n_InvalidAddressError); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 71; goto __pyx_L1;}
    Py_DECREF(__pyx_2); __pyx_2 = 0;
    __pyx_2 = PyTuple_New(2); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 71; goto __pyx_L1;}
    Py_INCREF(__pyx_v_address);
    PyTuple_SET_ITEM(__pyx_2, 0, __pyx_v_address);
    Py_INCREF(((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->name);
    PyTuple_SET_ITEM(__pyx_2, 1, ((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->name);
    __pyx_4 = PyObject_CallObject(__pyx_3, __pyx_2); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 71; goto __pyx_L1;}
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    Py_DECREF(__pyx_2); __pyx_2 = 0;
    __Pyx_Raise(__pyx_4, 0, 0);
    Py_DECREF(__pyx_4); __pyx_4 = 0;
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 71; goto __pyx_L1;}
    goto __pyx_L2;
  }
  /*else*/ {
    __pyx_3 = PyInt_FromLong(((struct __pyx_vtabstruct_8topology_Topology *)((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->__pyx_vtab)->pyx_isNormalized(((struct __pyx_obj_8topology_Topology *)__pyx_v_self),__pyx_v_address)); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 73; goto __pyx_L1;}
    __pyx_r = __pyx_3;
    __pyx_3 = 0;
    goto __pyx_L0;
  }
  __pyx_L2:;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  Py_XDECREF(__pyx_4);
  __Pyx_AddTraceback("topology.Topology.isNormalized");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  Py_DECREF(__pyx_v_address);
  return __pyx_r;
}

static int __pyx_f_8topology_8Topology_pyx_isNormalized(struct __pyx_obj_8topology_Topology *__pyx_v_self,PyObject *__pyx_v_address) {
  int __pyx_r;
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  int __pyx_3;
  Py_INCREF(__pyx_v_self);
  Py_INCREF(__pyx_v_address);
  __pyx_1 = ((struct __pyx_vtabstruct_8topology_Topology *)__pyx_v_self->__pyx_vtab)->pyx_normalize(__pyx_v_self,__pyx_v_address); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 82; goto __pyx_L1;}
  __pyx_2 = PyInt_FromLong((-1)); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 82; goto __pyx_L1;}
  if (PyObject_Cmp(__pyx_1, __pyx_2, &__pyx_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 82; goto __pyx_L1;}
  __pyx_3 = __pyx_3 == 0;
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  if (__pyx_3) {
    __pyx_r = (-1);
    goto __pyx_L0;
    goto __pyx_L2;
  }
  /*else*/ {
    __pyx_1 = ((struct __pyx_vtabstruct_8topology_Topology *)__pyx_v_self->__pyx_vtab)->pyx_normalize(__pyx_v_self,__pyx_v_address); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 85; goto __pyx_L1;}
    if (PyObject_Cmp(__pyx_v_address, __pyx_1, &__pyx_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 85; goto __pyx_L1;}
    __pyx_3 = __pyx_3 == 0;
    Py_DECREF(__pyx_1); __pyx_1 = 0;
    __pyx_r = __pyx_3;
    goto __pyx_L0;
  }
  __pyx_L2:;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  __Pyx_WriteUnraisable("topology.Topology.pyx_isNormalized");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  Py_DECREF(__pyx_v_address);
  return __pyx_r;
}

static PyObject *__pyx_f_8topology_8Topology_normalize(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_8topology_8Topology_normalize[] = "Normalise an address (depends strongly on the topology chosen)\n\n          address ---> a grid coordinate value in the form of a Python n-tuple\n          return  -->> a standard coordinate value";
static PyObject *__pyx_f_8topology_8Topology_normalize(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_address = 0;
  PyObject *__pyx_r;
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  int __pyx_3;
  PyObject *__pyx_4 = 0;
  static char *__pyx_argnames[] = {"address",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "O", __pyx_argnames, &__pyx_v_address)) return 0;
  Py_INCREF(__pyx_v_self);
  Py_INCREF(__pyx_v_address);
  __pyx_1 = ((struct __pyx_vtabstruct_8topology_Topology *)((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->__pyx_vtab)->pyx_normalize(((struct __pyx_obj_8topology_Topology *)__pyx_v_self),__pyx_v_address); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 94; goto __pyx_L1;}
  __pyx_2 = PyInt_FromLong((-1)); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 94; goto __pyx_L1;}
  if (PyObject_Cmp(__pyx_1, __pyx_2, &__pyx_3) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 94; goto __pyx_L1;}
  __pyx_3 = __pyx_3 == 0;
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  if (__pyx_3) {
    __pyx_1 = __Pyx_GetName(__pyx_m, __pyx_n_E); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 95; goto __pyx_L1;}
    __pyx_2 = PyObject_GetAttr(__pyx_1, __pyx_n_InvalidAddressError); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 95; goto __pyx_L1;}
    Py_DECREF(__pyx_1); __pyx_1 = 0;
    __pyx_1 = PyTuple_New(2); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 95; goto __pyx_L1;}
    Py_INCREF(__pyx_v_address);
    PyTuple_SET_ITEM(__pyx_1, 0, __pyx_v_address);
    Py_INCREF(((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->name);
    PyTuple_SET_ITEM(__pyx_1, 1, ((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->name);
    __pyx_4 = PyObject_CallObject(__pyx_2, __pyx_1); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 95; goto __pyx_L1;}
    Py_DECREF(__pyx_2); __pyx_2 = 0;
    Py_DECREF(__pyx_1); __pyx_1 = 0;
    __Pyx_Raise(__pyx_4, 0, 0);
    Py_DECREF(__pyx_4); __pyx_4 = 0;
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 95; goto __pyx_L1;}
    goto __pyx_L2;
  }
  /*else*/ {
    __pyx_2 = ((struct __pyx_vtabstruct_8topology_Topology *)((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->__pyx_vtab)->pyx_normalize(((struct __pyx_obj_8topology_Topology *)__pyx_v_self),__pyx_v_address); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 97; goto __pyx_L1;}
    __pyx_r = __pyx_2;
    __pyx_2 = 0;
    goto __pyx_L0;
  }
  __pyx_L2:;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_4);
  __Pyx_AddTraceback("topology.Topology.normalize");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  Py_DECREF(__pyx_v_address);
  return __pyx_r;
}

static PyObject *__pyx_f_8topology_8Topology_pyx_normalize(struct __pyx_obj_8topology_Topology *__pyx_v_self,PyObject *__pyx_v_address) {
  PyObject *__pyx_r;
  PyObject *__pyx_1 = 0;
  Py_INCREF(__pyx_v_self);
  Py_INCREF(__pyx_v_address);
  __pyx_1 = PyInt_FromLong((-1)); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 106; goto __pyx_L1;}
  __pyx_r = __pyx_1;
  __pyx_1 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  __Pyx_AddTraceback("topology.Topology.pyx_normalize");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  Py_DECREF(__pyx_v_address);
  return __pyx_r;
}

static PyObject *__pyx_f_8topology_8Topology_clone(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_8topology_8Topology_clone[] = "Create a twin instantiation of the same topology\n\n          return -->> a Topology with the same attributes as self";
static PyObject *__pyx_f_8topology_8Topology_clone(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_r;
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  static char *__pyx_argnames[] = {0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "", __pyx_argnames)) return 0;
  Py_INCREF(__pyx_v_self);
  __pyx_1 = PyInt_FromLong(((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->background); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 114; goto __pyx_L1;}
  __pyx_2 = PyTuple_New(2); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 114; goto __pyx_L1;}
  Py_INCREF(((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->size);
  PyTuple_SET_ITEM(__pyx_2, 0, ((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->size);
  PyTuple_SET_ITEM(__pyx_2, 1, __pyx_1);
  __pyx_1 = 0;
  __pyx_1 = PyObject_CallObject(((PyObject *)__pyx_ptype_8topology_Topology), __pyx_2); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 114; goto __pyx_L1;}
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  __pyx_r = __pyx_1;
  __pyx_1 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  __Pyx_AddTraceback("topology.Topology.clone");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  return __pyx_r;
}

static PyObject *__pyx_f_8topology_8Topology_get(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_8topology_8Topology_get[] = "Get the state at a given address\n\n          address ---> a grid coordinate value in the form of a Python n-tuple\n          return  -->> an integer";
static PyObject *__pyx_f_8topology_8Topology_get(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_address = 0;
  PyObject *__pyx_r;
  static char *__pyx_argnames[] = {"address",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "O", __pyx_argnames, &__pyx_v_address)) return 0;
  Py_INCREF(__pyx_v_self);
  Py_INCREF(__pyx_v_address);
  __Pyx_Raise(PyExc_NotImplementedError, 0, 0);
  {__pyx_filename = __pyx_f[0]; __pyx_lineno = 123; goto __pyx_L1;}

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  __Pyx_AddTraceback("topology.Topology.get");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  Py_DECREF(__pyx_v_address);
  return __pyx_r;
}

static PyObject *__pyx_f_8topology_8Topology_set(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_8topology_8Topology_set[] = "Set a given address to a given state\n\n          address ---> a grid coordinate value in the form of a Python n-tuple\n          state   ---> an integer\n          return  -->> None";
static PyObject *__pyx_f_8topology_8Topology_set(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_address = 0;
  int __pyx_v_state;
  PyObject *__pyx_r;
  static char *__pyx_argnames[] = {"address","state",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "Oi", __pyx_argnames, &__pyx_v_address, &__pyx_v_state)) return 0;
  Py_INCREF(__pyx_v_self);
  Py_INCREF(__pyx_v_address);
  __Pyx_Raise(PyExc_NotImplementedError, 0, 0);
  {__pyx_filename = __pyx_f[0]; __pyx_lineno = 133; goto __pyx_L1;}

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  __Pyx_AddTraceback("topology.Topology.set");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  Py_DECREF(__pyx_v_address);
  return __pyx_r;
}

static PyObject *__pyx_n_set;

static PyObject *__pyx_f_8topology_8Topology_reset(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_8topology_8Topology_reset[] = "Reset a cell to the predefined background state\n\n          address ---> a grid coordinate value in the form of a Python n-tuple\n          return  -->> None";
static PyObject *__pyx_f_8topology_8Topology_reset(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_address = 0;
  PyObject *__pyx_r;
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  static char *__pyx_argnames[] = {"address",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "O", __pyx_argnames, &__pyx_v_address)) return 0;
  Py_INCREF(__pyx_v_self);
  Py_INCREF(__pyx_v_address);
  __pyx_1 = PyObject_GetAttr(__pyx_v_self, __pyx_n_set); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 142; goto __pyx_L1;}
  __pyx_2 = PyInt_FromLong(((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->background); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 142; goto __pyx_L1;}
  __pyx_3 = PyTuple_New(2); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 142; goto __pyx_L1;}
  Py_INCREF(__pyx_v_address);
  PyTuple_SET_ITEM(__pyx_3, 0, __pyx_v_address);
  PyTuple_SET_ITEM(__pyx_3, 1, __pyx_2);
  __pyx_2 = 0;
  __pyx_2 = PyObject_CallObject(__pyx_1, __pyx_3); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 142; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  Py_DECREF(__pyx_3); __pyx_3 = 0;
  Py_DECREF(__pyx_2); __pyx_2 = 0;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  __Pyx_AddTraceback("topology.Topology.reset");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  Py_DECREF(__pyx_v_address);
  return __pyx_r;
}

static PyObject *__pyx_n_append;

static PyObject *__pyx_f_8topology_8Topology_center(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_8topology_8Topology_center[] = "Find a cell located roughly in the center of the grid.\n  \n          return -->> a Python n-tuple, the address of the above cell";
static PyObject *__pyx_f_8topology_8Topology_center(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_address;
  PyObject *__pyx_v_i;
  PyObject *__pyx_r;
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  PyObject *__pyx_4 = 0;
  PyObject *__pyx_5 = 0;
  static char *__pyx_argnames[] = {0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "", __pyx_argnames)) return 0;
  Py_INCREF(__pyx_v_self);
  __pyx_v_address = Py_None; Py_INCREF(Py_None);
  __pyx_v_i = Py_None; Py_INCREF(Py_None);

  /* "/home/panx/ouroborus/birdcage/topology.pyx":153 */
  __pyx_1 = PyList_New(0); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 153; goto __pyx_L1;}
  Py_DECREF(__pyx_v_address);
  __pyx_v_address = __pyx_1;
  __pyx_1 = 0;

  /* "/home/panx/ouroborus/birdcage/topology.pyx":154 */
  __pyx_1 = __Pyx_GetName(__pyx_b, __pyx_n_range); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 154; goto __pyx_L1;}
  __pyx_2 = PyInt_FromLong(((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->dimension); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 154; goto __pyx_L1;}
  __pyx_3 = PyTuple_New(1); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 154; goto __pyx_L1;}
  PyTuple_SET_ITEM(__pyx_3, 0, __pyx_2);
  __pyx_2 = 0;
  __pyx_2 = PyObject_CallObject(__pyx_1, __pyx_3); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 154; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  Py_DECREF(__pyx_3); __pyx_3 = 0;
  __pyx_1 = PyObject_GetIter(__pyx_2); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 154; goto __pyx_L1;}
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  for (;;) {
    __pyx_3 = PyIter_Next(__pyx_1);
    if (!__pyx_3) {
      if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 154; goto __pyx_L1;}
      break;
    }
    Py_DECREF(__pyx_v_i);
    __pyx_v_i = __pyx_3;
    __pyx_3 = 0;
    __pyx_2 = PyObject_GetAttr(__pyx_v_address, __pyx_n_append); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 155; goto __pyx_L1;}
    __pyx_3 = PyObject_GetItem(((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->size, __pyx_v_i); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 155; goto __pyx_L1;}
    __pyx_4 = PyInt_FromLong(2); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 155; goto __pyx_L1;}
    __pyx_5 = PyNumber_Divide(__pyx_3, __pyx_4); if (!__pyx_5) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 155; goto __pyx_L1;}
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    Py_DECREF(__pyx_4); __pyx_4 = 0;
    __pyx_3 = PyTuple_New(1); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 155; goto __pyx_L1;}
    PyTuple_SET_ITEM(__pyx_3, 0, __pyx_5);
    __pyx_5 = 0;
    __pyx_4 = PyObject_CallObject(__pyx_2, __pyx_3); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 155; goto __pyx_L1;}
    Py_DECREF(__pyx_2); __pyx_2 = 0;
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    Py_DECREF(__pyx_4); __pyx_4 = 0;
  }
  Py_DECREF(__pyx_1); __pyx_1 = 0;

  /* "/home/panx/ouroborus/birdcage/topology.pyx":156 */
  __pyx_5 = PyTuple_New(1); if (!__pyx_5) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 156; goto __pyx_L1;}
  Py_INCREF(__pyx_v_address);
  PyTuple_SET_ITEM(__pyx_5, 0, __pyx_v_address);
  __pyx_2 = PyObject_CallObject(((PyObject *)(&PyTuple_Type)), __pyx_5); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 156; goto __pyx_L1;}
  Py_DECREF(__pyx_5); __pyx_5 = 0;
  __pyx_r = __pyx_2;
  __pyx_2 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  Py_XDECREF(__pyx_4);
  Py_XDECREF(__pyx_5);
  __Pyx_AddTraceback("topology.Topology.center");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_address);
  Py_DECREF(__pyx_v_i);
  Py_DECREF(__pyx_v_self);
  return __pyx_r;
}

static PyObject *__pyx_n_map;
static PyObject *__pyx_n_randrange;

static PyObject *__pyx_f_8topology_8Topology_random(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_8topology_8Topology_random[] = "Find a random, valid address in the grid.        \n  \n          return -->> a Python n-tuple";
static PyObject *__pyx_f_8topology_8Topology_random(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_address;
  PyObject *__pyx_r;
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  static char *__pyx_argnames[] = {0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "", __pyx_argnames)) return 0;
  Py_INCREF(__pyx_v_self);
  __pyx_v_address = Py_None; Py_INCREF(Py_None);

  /* "/home/panx/ouroborus/birdcage/topology.pyx":167 */
  __pyx_1 = __Pyx_GetName(__pyx_b, __pyx_n_map); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 167; goto __pyx_L1;}
  __pyx_2 = __Pyx_GetName(__pyx_m, __pyx_n_random); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 167; goto __pyx_L1;}
  __pyx_3 = PyObject_GetAttr(__pyx_2, __pyx_n_randrange); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 167; goto __pyx_L1;}
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  __pyx_2 = PyTuple_New(2); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 167; goto __pyx_L1;}
  PyTuple_SET_ITEM(__pyx_2, 0, __pyx_3);
  Py_INCREF(((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->size);
  PyTuple_SET_ITEM(__pyx_2, 1, ((struct __pyx_obj_8topology_Topology *)__pyx_v_self)->size);
  __pyx_3 = 0;
  __pyx_3 = PyObject_CallObject(__pyx_1, __pyx_2); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 167; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  Py_DECREF(__pyx_v_address);
  __pyx_v_address = __pyx_3;
  __pyx_3 = 0;

  /* "/home/panx/ouroborus/birdcage/topology.pyx":168 */
  __pyx_1 = PyTuple_New(1); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 168; goto __pyx_L1;}
  Py_INCREF(__pyx_v_address);
  PyTuple_SET_ITEM(__pyx_1, 0, __pyx_v_address);
  __pyx_2 = PyObject_CallObject(((PyObject *)(&PyTuple_Type)), __pyx_1); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 168; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  __pyx_r = __pyx_2;
  __pyx_2 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  __Pyx_AddTraceback("topology.Topology.random");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_address);
  Py_DECREF(__pyx_v_self);
  return __pyx_r;
}

static PyObject *__pyx_n___init__;
static PyObject *__pyx_n_DimensionError;

static PyObject *__pyx_k5p;

static char __pyx_k5[] = "Grid Topology";

static int __pyx_f_8topology_12GridTopology___init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static int __pyx_f_8topology_12GridTopology___init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_size = 0;
  int __pyx_v_background;
  int __pyx_v_x1;
  int __pyx_v_x2;
  int __pyx_r;
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  int __pyx_4;
  PyObject *__pyx_5 = 0;
  int __pyx_6;
  static char *__pyx_argnames[] = {"size","background",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "Oi", __pyx_argnames, &__pyx_v_size, &__pyx_v_background)) return -1;
  Py_INCREF((PyObject *)__pyx_v_self);
  Py_INCREF(__pyx_v_size);

  /* "/home/panx/ouroborus/birdcage/topology.pyx":190 */
  __pyx_1 = PyObject_GetAttr(((PyObject *)__pyx_ptype_8topology_Topology), __pyx_n___init__); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 190; goto __pyx_L1;}
  __pyx_2 = PyInt_FromLong(__pyx_v_background); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 190; goto __pyx_L1;}
  __pyx_3 = PyTuple_New(3); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 190; goto __pyx_L1;}
  Py_INCREF(__pyx_v_self);
  PyTuple_SET_ITEM(__pyx_3, 0, __pyx_v_self);
  Py_INCREF(__pyx_v_size);
  PyTuple_SET_ITEM(__pyx_3, 1, __pyx_v_size);
  PyTuple_SET_ITEM(__pyx_3, 2, __pyx_2);
  __pyx_2 = 0;
  __pyx_2 = PyObject_CallObject(__pyx_1, __pyx_3); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 190; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  Py_DECREF(__pyx_3); __pyx_3 = 0;
  Py_DECREF(__pyx_2); __pyx_2 = 0;

  /* "/home/panx/ouroborus/birdcage/topology.pyx":191 */
  Py_INCREF(__pyx_k5p);
  Py_DECREF(((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self)->__pyx_base.name);
  ((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self)->__pyx_base.name = __pyx_k5p;

  /* "/home/panx/ouroborus/birdcage/topology.pyx":192 */
  __pyx_4 = (!(((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self)->__pyx_base.dimension == 2));
  if (__pyx_4) {
    __pyx_1 = __Pyx_GetName(__pyx_m, __pyx_n_E); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 193; goto __pyx_L1;}
    __pyx_3 = PyObject_GetAttr(__pyx_1, __pyx_n_DimensionError); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 193; goto __pyx_L1;}
    Py_DECREF(__pyx_1); __pyx_1 = 0;
    __pyx_2 = PyInt_FromLong(2); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 193; goto __pyx_L1;}
    __pyx_1 = PyInt_FromLong(((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self)->__pyx_base.dimension); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 193; goto __pyx_L1;}
    __pyx_5 = PyTuple_New(3); if (!__pyx_5) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 193; goto __pyx_L1;}
    Py_INCREF(((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self)->__pyx_base.name);
    PyTuple_SET_ITEM(__pyx_5, 0, ((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self)->__pyx_base.name);
    PyTuple_SET_ITEM(__pyx_5, 1, __pyx_2);
    PyTuple_SET_ITEM(__pyx_5, 2, __pyx_1);
    __pyx_2 = 0;
    __pyx_1 = 0;
    __pyx_2 = PyObject_CallObject(__pyx_3, __pyx_5); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 193; goto __pyx_L1;}
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    Py_DECREF(__pyx_5); __pyx_5 = 0;
    __Pyx_Raise(__pyx_2, 0, 0);
    Py_DECREF(__pyx_2); __pyx_2 = 0;
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 193; goto __pyx_L1;}
    goto __pyx_L2;
  }
  __pyx_L2:;

  /* "/home/panx/ouroborus/birdcage/topology.pyx":194 */
  __pyx_1 = PyObject_GetIter(__pyx_v_size); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 194; goto __pyx_L1;}
  __pyx_3 = __Pyx_UnpackItem(__pyx_1); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 194; goto __pyx_L1;}
  __pyx_4 = PyInt_AsLong(__pyx_3); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 194; goto __pyx_L1;}
  Py_DECREF(__pyx_3); __pyx_3 = 0;
  ((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self)->width = __pyx_4;
  __pyx_5 = __Pyx_UnpackItem(__pyx_1); if (!__pyx_5) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 194; goto __pyx_L1;}
  __pyx_4 = PyInt_AsLong(__pyx_5); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 194; goto __pyx_L1;}
  Py_DECREF(__pyx_5); __pyx_5 = 0;
  ((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self)->height = __pyx_4;
  if (__Pyx_EndUnpack(__pyx_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 194; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;

  /* "/home/panx/ouroborus/birdcage/topology.pyx":195 */
  ((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self)->border = 0;

  /* "/home/panx/ouroborus/birdcage/topology.pyx":199 */
  __pyx_4 = ((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self)->width;
  for (__pyx_v_x1 = 0; __pyx_v_x1 < __pyx_4; ++__pyx_v_x1) {
    __pyx_6 = ((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self)->height;
    for (__pyx_v_x2 = 0; __pyx_v_x2 < __pyx_6; ++__pyx_v_x2) {
      ((((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self)->cell[__pyx_v_x1])[__pyx_v_x2]) = __pyx_v_background;
    }
  }

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  Py_XDECREF(__pyx_5);
  __Pyx_AddTraceback("topology.GridTopology.__init__");
  __pyx_r = -1;
  __pyx_L0:;
  Py_DECREF((PyObject *)__pyx_v_self);
  Py_DECREF(__pyx_v_size);
  return __pyx_r;
}

static PyObject *__pyx_f_8topology_12GridTopology_clone(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_8topology_12GridTopology_clone[] = "Create a twin instantiation of the same topology\n\n          return -->> a Topology with the same attributes as self";
static PyObject *__pyx_f_8topology_12GridTopology_clone(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_r;
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  static char *__pyx_argnames[] = {0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "", __pyx_argnames)) return 0;
  Py_INCREF((PyObject *)__pyx_v_self);
  __pyx_1 = PyInt_FromLong(((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self)->__pyx_base.background); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 209; goto __pyx_L1;}
  __pyx_2 = PyTuple_New(2); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 209; goto __pyx_L1;}
  Py_INCREF(((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self)->__pyx_base.size);
  PyTuple_SET_ITEM(__pyx_2, 0, ((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self)->__pyx_base.size);
  PyTuple_SET_ITEM(__pyx_2, 1, __pyx_1);
  __pyx_1 = 0;
  __pyx_1 = PyObject_CallObject(((PyObject *)__pyx_ptype_8topology_GridTopology), __pyx_2); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 209; goto __pyx_L1;}
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  __pyx_r = __pyx_1;
  __pyx_1 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  __Pyx_AddTraceback("topology.GridTopology.clone");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF((PyObject *)__pyx_v_self);
  return __pyx_r;
}

static PyObject *__pyx_f_8topology_12GridTopology_pyx_normalize(struct __pyx_obj_8topology_GridTopology *__pyx_v_self,PyObject *__pyx_v_address) {
  PyObject *__pyx_r;
  Py_ssize_t __pyx_1;
  int __pyx_2;
  PyObject *__pyx_3 = 0;
  int __pyx_4;
  PyObject *__pyx_5 = 0;
  PyObject *__pyx_6 = 0;
  Py_INCREF((PyObject *)__pyx_v_self);
  Py_INCREF(__pyx_v_address);
  __pyx_1 = PyObject_Length(__pyx_v_address); if (__pyx_1 == -1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 218; goto __pyx_L1;}
  __pyx_2 = (__pyx_1 > 2);
  if (__pyx_2) {
    __pyx_3 = PyInt_FromLong((-1)); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 219; goto __pyx_L1;}
    __pyx_r = __pyx_3;
    __pyx_3 = 0;
    goto __pyx_L0;
    goto __pyx_L2;
  }
  __pyx_3 = __Pyx_GetItemInt(__pyx_v_address, 0); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 220; goto __pyx_L1;}
  __pyx_4 = PyInt_AsLong(__pyx_3); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 220; goto __pyx_L1;}
  Py_DECREF(__pyx_3); __pyx_3 = 0;
  __pyx_2 = (((struct __pyx_vtabstruct_8topology_GridTopology *)__pyx_v_self->__pyx_base.__pyx_vtab)->normal_x1(__pyx_v_self,__pyx_4) == (-1));
  if (!__pyx_2) {
    __pyx_3 = __Pyx_GetItemInt(__pyx_v_address, 1); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 220; goto __pyx_L1;}
    __pyx_4 = PyInt_AsLong(__pyx_3); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 220; goto __pyx_L1;}
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    __pyx_2 = (((struct __pyx_vtabstruct_8topology_GridTopology *)__pyx_v_self->__pyx_base.__pyx_vtab)->normal_x2(__pyx_v_self,__pyx_4) == (-1));
  }
  if (__pyx_2) {
    __pyx_3 = PyInt_FromLong((-1)); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 221; goto __pyx_L1;}
    __pyx_r = __pyx_3;
    __pyx_3 = 0;
    goto __pyx_L0;
    goto __pyx_L2;
  }
  /*else*/ {
    __pyx_3 = __Pyx_GetItemInt(__pyx_v_address, 0); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 223; goto __pyx_L1;}
    __pyx_4 = PyInt_AsLong(__pyx_3); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 223; goto __pyx_L1;}
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    __pyx_3 = PyInt_FromLong(((struct __pyx_vtabstruct_8topology_GridTopology *)__pyx_v_self->__pyx_base.__pyx_vtab)->normal_x1(__pyx_v_self,__pyx_4)); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 223; goto __pyx_L1;}
    __pyx_5 = __Pyx_GetItemInt(__pyx_v_address, 1); if (!__pyx_5) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 223; goto __pyx_L1;}
    __pyx_2 = PyInt_AsLong(__pyx_5); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 223; goto __pyx_L1;}
    Py_DECREF(__pyx_5); __pyx_5 = 0;
    __pyx_5 = PyInt_FromLong(((struct __pyx_vtabstruct_8topology_GridTopology *)__pyx_v_self->__pyx_base.__pyx_vtab)->normal_x2(__pyx_v_self,__pyx_2)); if (!__pyx_5) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 223; goto __pyx_L1;}
    __pyx_6 = PyTuple_New(2); if (!__pyx_6) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 223; goto __pyx_L1;}
    PyTuple_SET_ITEM(__pyx_6, 0, __pyx_3);
    PyTuple_SET_ITEM(__pyx_6, 1, __pyx_5);
    __pyx_3 = 0;
    __pyx_5 = 0;
    __pyx_r = __pyx_6;
    __pyx_6 = 0;
    goto __pyx_L0;
  }
  __pyx_L2:;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_3);
  Py_XDECREF(__pyx_5);
  Py_XDECREF(__pyx_6);
  __Pyx_AddTraceback("topology.GridTopology.pyx_normalize");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF((PyObject *)__pyx_v_self);
  Py_DECREF(__pyx_v_address);
  return __pyx_r;
}

static int __pyx_f_8topology_12GridTopology_normal_x1(struct __pyx_obj_8topology_GridTopology *__pyx_v_self,int __pyx_v_x1) {
  int __pyx_r;
  int __pyx_1;
  Py_INCREF((PyObject *)__pyx_v_self);
  __pyx_1 = (__pyx_v_x1 < 0);
  if (!__pyx_1) {
    __pyx_1 = (__pyx_v_x1 >= __pyx_v_self->width);
  }
  if (__pyx_1) {
    __pyx_r = (-1);
    goto __pyx_L0;
    goto __pyx_L2;
  }
  /*else*/ {
    __pyx_r = __pyx_v_x1;
    goto __pyx_L0;
  }
  __pyx_L2:;

  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF((PyObject *)__pyx_v_self);
  return __pyx_r;
}

static int __pyx_f_8topology_12GridTopology_normal_x2(struct __pyx_obj_8topology_GridTopology *__pyx_v_self,int __pyx_v_x2) {
  int __pyx_r;
  int __pyx_1;
  Py_INCREF((PyObject *)__pyx_v_self);
  __pyx_1 = (__pyx_v_x2 < 0);
  if (!__pyx_1) {
    __pyx_1 = (__pyx_v_x2 >= __pyx_v_self->height);
  }
  if (__pyx_1) {
    __pyx_r = (-1);
    goto __pyx_L0;
    goto __pyx_L2;
  }
  /*else*/ {
    __pyx_r = __pyx_v_x2;
    goto __pyx_L0;
  }
  __pyx_L2:;

  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF((PyObject *)__pyx_v_self);
  return __pyx_r;
}

static PyObject *__pyx_f_8topology_12GridTopology_get(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_8topology_12GridTopology_get[] = "Get the state at a given address\n\n          address ---> a grid coordinate value in the form of a Python 2-tuple\n          return  -->> an integer";
static PyObject *__pyx_f_8topology_12GridTopology_get(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
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
  Py_INCREF((PyObject *)__pyx_v_self);
  Py_INCREF(__pyx_v_address);
  __pyx_1 = PyObject_Length(__pyx_v_address); if (__pyx_1 == -1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 256; goto __pyx_L1;}
  __pyx_2 = (!(__pyx_1 == 2));
  if (__pyx_2) {
    __pyx_3 = __Pyx_GetName(__pyx_m, __pyx_n_E); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 257; goto __pyx_L1;}
    __pyx_4 = PyObject_GetAttr(__pyx_3, __pyx_n_InvalidAddressError); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 257; goto __pyx_L1;}
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    __pyx_3 = PyTuple_New(2); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 257; goto __pyx_L1;}
    Py_INCREF(__pyx_v_address);
    PyTuple_SET_ITEM(__pyx_3, 0, __pyx_v_address);
    Py_INCREF(((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self)->__pyx_base.name);
    PyTuple_SET_ITEM(__pyx_3, 1, ((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self)->__pyx_base.name);
    __pyx_5 = PyObject_CallObject(__pyx_4, __pyx_3); if (!__pyx_5) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 257; goto __pyx_L1;}
    Py_DECREF(__pyx_4); __pyx_4 = 0;
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    __Pyx_Raise(__pyx_5, 0, 0);
    Py_DECREF(__pyx_5); __pyx_5 = 0;
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 257; goto __pyx_L1;}
    goto __pyx_L2;
  }
  /*else*/ {
    __pyx_4 = __Pyx_GetItemInt(__pyx_v_address, 0); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 259; goto __pyx_L1;}
    __pyx_2 = PyInt_AsLong(__pyx_4); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 259; goto __pyx_L1;}
    Py_DECREF(__pyx_4); __pyx_4 = 0;
    __pyx_3 = __Pyx_GetItemInt(__pyx_v_address, 1); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 259; goto __pyx_L1;}
    __pyx_6 = PyInt_AsLong(__pyx_3); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 259; goto __pyx_L1;}
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    __pyx_5 = PyInt_FromLong(((struct __pyx_vtabstruct_8topology_GridTopology *)((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self)->__pyx_base.__pyx_vtab)->pyx_get(((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self),__pyx_2,__pyx_6)); if (!__pyx_5) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 259; goto __pyx_L1;}
    __pyx_r = __pyx_5;
    __pyx_5 = 0;
    goto __pyx_L0;
  }
  __pyx_L2:;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_3);
  Py_XDECREF(__pyx_4);
  Py_XDECREF(__pyx_5);
  __Pyx_AddTraceback("topology.GridTopology.get");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF((PyObject *)__pyx_v_self);
  Py_DECREF(__pyx_v_address);
  return __pyx_r;
}

static int __pyx_f_8topology_12GridTopology_pyx_get(struct __pyx_obj_8topology_GridTopology *__pyx_v_self,int __pyx_v_x1,int __pyx_v_x2) {
  int __pyx_v_nx1;
  int __pyx_v_nx2;
  int __pyx_r;
  int __pyx_1;
  Py_INCREF((PyObject *)__pyx_v_self);

  /* "/home/panx/ouroborus/birdcage/topology.pyx":270 */
  __pyx_v_nx1 = ((struct __pyx_vtabstruct_8topology_GridTopology *)__pyx_v_self->__pyx_base.__pyx_vtab)->normal_x1(__pyx_v_self,__pyx_v_x1);

  /* "/home/panx/ouroborus/birdcage/topology.pyx":271 */
  __pyx_v_nx2 = ((struct __pyx_vtabstruct_8topology_GridTopology *)__pyx_v_self->__pyx_base.__pyx_vtab)->normal_x2(__pyx_v_self,__pyx_v_x2);

  /* "/home/panx/ouroborus/birdcage/topology.pyx":272 */
  __pyx_1 = (__pyx_v_nx1 == (-1));
  if (!__pyx_1) {
    __pyx_1 = (__pyx_v_nx2 == (-1));
  }
  if (__pyx_1) {
    __pyx_r = __pyx_v_self->border;
    goto __pyx_L0;
    goto __pyx_L2;
  }
  /*else*/ {
    __pyx_r = ((__pyx_v_self->cell[__pyx_v_nx1])[__pyx_v_nx2]);
    goto __pyx_L0;
  }
  __pyx_L2:;

  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF((PyObject *)__pyx_v_self);
  return __pyx_r;
}

static int __pyx_f_8topology_12GridTopology_pyx_get_nosafe(struct __pyx_obj_8topology_GridTopology *__pyx_v_self,int __pyx_v_x1,int __pyx_v_x2) {
  int __pyx_r;
  Py_INCREF((PyObject *)__pyx_v_self);
  __pyx_r = ((__pyx_v_self->cell[__pyx_v_x1])[__pyx_v_x2]);
  goto __pyx_L0;

  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF((PyObject *)__pyx_v_self);
  return __pyx_r;
}

static PyObject *__pyx_f_8topology_12GridTopology_set(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_8topology_12GridTopology_set[] = "Set a given address to a given state\n\n          address ---> a grid coordinate value in the form of a Python 2-tuple\n          state   ---> an integer\n          return  -->> None";
static PyObject *__pyx_f_8topology_12GridTopology_set(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_address = 0;
  int __pyx_v_state;
  PyObject *__pyx_v_s;
  PyObject *__pyx_r;
  Py_ssize_t __pyx_1;
  int __pyx_2;
  PyObject *__pyx_3 = 0;
  PyObject *__pyx_4 = 0;
  PyObject *__pyx_5 = 0;
  int __pyx_6;
  static char *__pyx_argnames[] = {"address","state",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "Oi", __pyx_argnames, &__pyx_v_address, &__pyx_v_state)) return 0;
  Py_INCREF((PyObject *)__pyx_v_self);
  Py_INCREF(__pyx_v_address);
  __pyx_v_s = Py_None; Py_INCREF(Py_None);

  /* "/home/panx/ouroborus/birdcage/topology.pyx":295 */
  __pyx_1 = PyObject_Length(__pyx_v_address); if (__pyx_1 == -1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 295; goto __pyx_L1;}
  __pyx_2 = (!(__pyx_1 == 2));
  if (__pyx_2) {
    __pyx_3 = __Pyx_GetName(__pyx_m, __pyx_n_E); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 296; goto __pyx_L1;}
    __pyx_4 = PyObject_GetAttr(__pyx_3, __pyx_n_InvalidAddressError); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 296; goto __pyx_L1;}
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    __pyx_3 = PyTuple_New(2); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 296; goto __pyx_L1;}
    Py_INCREF(__pyx_v_address);
    PyTuple_SET_ITEM(__pyx_3, 0, __pyx_v_address);
    Py_INCREF(((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self)->__pyx_base.name);
    PyTuple_SET_ITEM(__pyx_3, 1, ((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self)->__pyx_base.name);
    __pyx_5 = PyObject_CallObject(__pyx_4, __pyx_3); if (!__pyx_5) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 296; goto __pyx_L1;}
    Py_DECREF(__pyx_4); __pyx_4 = 0;
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    __Pyx_Raise(__pyx_5, 0, 0);
    Py_DECREF(__pyx_5); __pyx_5 = 0;
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 296; goto __pyx_L1;}
    goto __pyx_L2;
  }
  /*else*/ {
    __pyx_4 = __Pyx_GetItemInt(__pyx_v_address, 0); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 298; goto __pyx_L1;}
    __pyx_2 = PyInt_AsLong(__pyx_4); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 298; goto __pyx_L1;}
    Py_DECREF(__pyx_4); __pyx_4 = 0;
    __pyx_3 = __Pyx_GetItemInt(__pyx_v_address, 1); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 298; goto __pyx_L1;}
    __pyx_6 = PyInt_AsLong(__pyx_3); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 298; goto __pyx_L1;}
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    __pyx_5 = PyInt_FromLong(((struct __pyx_vtabstruct_8topology_GridTopology *)((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self)->__pyx_base.__pyx_vtab)->pyx_set(((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self),__pyx_2,__pyx_6,__pyx_v_state)); if (!__pyx_5) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 298; goto __pyx_L1;}
    Py_DECREF(__pyx_v_s);
    __pyx_v_s = __pyx_5;
    __pyx_5 = 0;
  }
  __pyx_L2:;

  /* "/home/panx/ouroborus/birdcage/topology.pyx":299 */
  __pyx_4 = PyInt_FromLong(0); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 299; goto __pyx_L1;}
  if (PyObject_Cmp(__pyx_v_s, __pyx_4, &__pyx_2) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 299; goto __pyx_L1;}
  __pyx_2 = __pyx_2 == 0;
  Py_DECREF(__pyx_4); __pyx_4 = 0;
  __pyx_6 = (!__pyx_2);
  if (__pyx_6) {
    __pyx_3 = __Pyx_GetName(__pyx_m, __pyx_n_E); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 300; goto __pyx_L1;}
    __pyx_5 = PyObject_GetAttr(__pyx_3, __pyx_n_InvalidAddressError); if (!__pyx_5) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 300; goto __pyx_L1;}
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    __pyx_4 = PyTuple_New(2); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 300; goto __pyx_L1;}
    Py_INCREF(__pyx_v_address);
    PyTuple_SET_ITEM(__pyx_4, 0, __pyx_v_address);
    Py_INCREF(((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self)->__pyx_base.name);
    PyTuple_SET_ITEM(__pyx_4, 1, ((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self)->__pyx_base.name);
    __pyx_3 = PyObject_CallObject(__pyx_5, __pyx_4); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 300; goto __pyx_L1;}
    Py_DECREF(__pyx_5); __pyx_5 = 0;
    Py_DECREF(__pyx_4); __pyx_4 = 0;
    __Pyx_Raise(__pyx_3, 0, 0);
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 300; goto __pyx_L1;}
    goto __pyx_L3;
  }
  __pyx_L3:;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_3);
  Py_XDECREF(__pyx_4);
  Py_XDECREF(__pyx_5);
  __Pyx_AddTraceback("topology.GridTopology.set");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_s);
  Py_DECREF((PyObject *)__pyx_v_self);
  Py_DECREF(__pyx_v_address);
  return __pyx_r;
}

static int __pyx_f_8topology_12GridTopology_pyx_set(struct __pyx_obj_8topology_GridTopology *__pyx_v_self,int __pyx_v_x1,int __pyx_v_x2,int __pyx_v_state) {
  int __pyx_v_nx1;
  int __pyx_v_nx2;
  int __pyx_r;
  int __pyx_1;
  Py_INCREF((PyObject *)__pyx_v_self);

  /* "/home/panx/ouroborus/birdcage/topology.pyx":312 */
  __pyx_v_nx1 = ((struct __pyx_vtabstruct_8topology_GridTopology *)__pyx_v_self->__pyx_base.__pyx_vtab)->normal_x1(__pyx_v_self,__pyx_v_x1);

  /* "/home/panx/ouroborus/birdcage/topology.pyx":313 */
  __pyx_v_nx2 = ((struct __pyx_vtabstruct_8topology_GridTopology *)__pyx_v_self->__pyx_base.__pyx_vtab)->normal_x2(__pyx_v_self,__pyx_v_x2);

  /* "/home/panx/ouroborus/birdcage/topology.pyx":314 */
  __pyx_1 = (__pyx_v_nx1 == (-1));
  if (!__pyx_1) {
    __pyx_1 = (__pyx_v_nx2 == (-1));
  }
  if (__pyx_1) {
    __pyx_r = (-1);
    goto __pyx_L0;
    goto __pyx_L2;
  }
  /*else*/ {

    /* "/home/panx/ouroborus/birdcage/topology.pyx":317 */
    ((__pyx_v_self->cell[__pyx_v_nx1])[__pyx_v_nx2]) = __pyx_v_state;

    /* "/home/panx/ouroborus/birdcage/topology.pyx":318 */
    __pyx_r = 0;
    goto __pyx_L0;
  }
  __pyx_L2:;

  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF((PyObject *)__pyx_v_self);
  return __pyx_r;
}

static void __pyx_f_8topology_12GridTopology_pyx_set_nosafe(struct __pyx_obj_8topology_GridTopology *__pyx_v_self,int __pyx_v_x1,int __pyx_v_x2,int __pyx_v_state) {
  Py_INCREF((PyObject *)__pyx_v_self);
  ((__pyx_v_self->cell[__pyx_v_x1])[__pyx_v_x2]) = __pyx_v_state;

  Py_DECREF((PyObject *)__pyx_v_self);
}

static PyObject *__pyx_k6p;

static char __pyx_k6[] = "Toroid Topology";

static int __pyx_f_8topology_14ToroidTopology___init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static int __pyx_f_8topology_14ToroidTopology___init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_size = 0;
  int __pyx_v_background;
  int __pyx_r;
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  static char *__pyx_argnames[] = {"size","background",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "Oi", __pyx_argnames, &__pyx_v_size, &__pyx_v_background)) return -1;
  Py_INCREF((PyObject *)__pyx_v_self);
  Py_INCREF(__pyx_v_size);

  /* "/home/panx/ouroborus/birdcage/topology.pyx":348 */
  __pyx_1 = PyObject_GetAttr(((PyObject *)__pyx_ptype_8topology_GridTopology), __pyx_n___init__); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 348; goto __pyx_L1;}
  __pyx_2 = PyInt_FromLong(__pyx_v_background); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 348; goto __pyx_L1;}
  __pyx_3 = PyTuple_New(3); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 348; goto __pyx_L1;}
  Py_INCREF(__pyx_v_self);
  PyTuple_SET_ITEM(__pyx_3, 0, __pyx_v_self);
  Py_INCREF(__pyx_v_size);
  PyTuple_SET_ITEM(__pyx_3, 1, __pyx_v_size);
  PyTuple_SET_ITEM(__pyx_3, 2, __pyx_2);
  __pyx_2 = 0;
  __pyx_2 = PyObject_CallObject(__pyx_1, __pyx_3); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 348; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  Py_DECREF(__pyx_3); __pyx_3 = 0;
  Py_DECREF(__pyx_2); __pyx_2 = 0;

  /* "/home/panx/ouroborus/birdcage/topology.pyx":349 */
  Py_INCREF(__pyx_k6p);
  Py_DECREF(((struct __pyx_obj_8topology_ToroidTopology *)__pyx_v_self)->__pyx_base.__pyx_base.name);
  ((struct __pyx_obj_8topology_ToroidTopology *)__pyx_v_self)->__pyx_base.__pyx_base.name = __pyx_k6p;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  __Pyx_AddTraceback("topology.ToroidTopology.__init__");
  __pyx_r = -1;
  __pyx_L0:;
  Py_DECREF((PyObject *)__pyx_v_self);
  Py_DECREF(__pyx_v_size);
  return __pyx_r;
}

static PyObject *__pyx_f_8topology_14ToroidTopology_clone(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_8topology_14ToroidTopology_clone[] = "Create a twin instantiation of the same topology\n\n          return -->> a Topology with the same attributes as self";
static PyObject *__pyx_f_8topology_14ToroidTopology_clone(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_r;
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  static char *__pyx_argnames[] = {0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "", __pyx_argnames)) return 0;
  Py_INCREF((PyObject *)__pyx_v_self);
  __pyx_1 = PyInt_FromLong(((struct __pyx_obj_8topology_ToroidTopology *)__pyx_v_self)->__pyx_base.__pyx_base.background); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 357; goto __pyx_L1;}
  __pyx_2 = PyTuple_New(2); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 357; goto __pyx_L1;}
  Py_INCREF(((struct __pyx_obj_8topology_ToroidTopology *)__pyx_v_self)->__pyx_base.__pyx_base.size);
  PyTuple_SET_ITEM(__pyx_2, 0, ((struct __pyx_obj_8topology_ToroidTopology *)__pyx_v_self)->__pyx_base.__pyx_base.size);
  PyTuple_SET_ITEM(__pyx_2, 1, __pyx_1);
  __pyx_1 = 0;
  __pyx_1 = PyObject_CallObject(((PyObject *)__pyx_ptype_8topology_ToroidTopology), __pyx_2); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 357; goto __pyx_L1;}
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  __pyx_r = __pyx_1;
  __pyx_1 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  __Pyx_AddTraceback("topology.ToroidTopology.clone");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF((PyObject *)__pyx_v_self);
  return __pyx_r;
}

static PyObject *__pyx_f_8topology_14ToroidTopology_pyx_normalize(struct __pyx_obj_8topology_ToroidTopology *__pyx_v_self,PyObject *__pyx_v_address) {
  PyObject *__pyx_r;
  Py_ssize_t __pyx_1;
  int __pyx_2;
  PyObject *__pyx_3 = 0;
  PyObject *__pyx_4 = 0;
  PyObject *__pyx_5 = 0;
  Py_INCREF((PyObject *)__pyx_v_self);
  Py_INCREF(__pyx_v_address);
  __pyx_1 = PyObject_Length(__pyx_v_address); if (__pyx_1 == -1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 366; goto __pyx_L1;}
  __pyx_2 = (__pyx_1 > 2);
  if (__pyx_2) {
    __pyx_3 = PyInt_FromLong((-1)); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 367; goto __pyx_L1;}
    __pyx_r = __pyx_3;
    __pyx_3 = 0;
    goto __pyx_L0;
    goto __pyx_L2;
  }
  /*else*/ {
    __pyx_3 = __Pyx_GetItemInt(__pyx_v_address, 0); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 369; goto __pyx_L1;}
    __pyx_2 = PyInt_AsLong(__pyx_3); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 369; goto __pyx_L1;}
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    __pyx_3 = PyInt_FromLong(((struct __pyx_vtabstruct_8topology_ToroidTopology *)__pyx_v_self->__pyx_base.__pyx_base.__pyx_vtab)->__pyx_base.normal_x1(((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self),__pyx_2)); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 369; goto __pyx_L1;}
    __pyx_4 = __Pyx_GetItemInt(__pyx_v_address, 1); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 369; goto __pyx_L1;}
    __pyx_2 = PyInt_AsLong(__pyx_4); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 369; goto __pyx_L1;}
    Py_DECREF(__pyx_4); __pyx_4 = 0;
    __pyx_4 = PyInt_FromLong(((struct __pyx_vtabstruct_8topology_ToroidTopology *)__pyx_v_self->__pyx_base.__pyx_base.__pyx_vtab)->__pyx_base.normal_x2(((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self),__pyx_2)); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 369; goto __pyx_L1;}
    __pyx_5 = PyTuple_New(2); if (!__pyx_5) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 369; goto __pyx_L1;}
    PyTuple_SET_ITEM(__pyx_5, 0, __pyx_3);
    PyTuple_SET_ITEM(__pyx_5, 1, __pyx_4);
    __pyx_3 = 0;
    __pyx_4 = 0;
    __pyx_r = __pyx_5;
    __pyx_5 = 0;
    goto __pyx_L0;
  }
  __pyx_L2:;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_3);
  Py_XDECREF(__pyx_4);
  Py_XDECREF(__pyx_5);
  __Pyx_AddTraceback("topology.ToroidTopology.pyx_normalize");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF((PyObject *)__pyx_v_self);
  Py_DECREF(__pyx_v_address);
  return __pyx_r;
}

static int __pyx_f_8topology_14ToroidTopology_normal_x1(struct __pyx_obj_8topology_ToroidTopology *__pyx_v_self,int __pyx_v_x1) {
  int __pyx_r;
  int __pyx_1;
  Py_INCREF((PyObject *)__pyx_v_self);

  /* "/home/panx/ouroborus/birdcage/topology.pyx":378 */
  while (1) {
    __pyx_1 = (__pyx_v_x1 < 0);
    if (!__pyx_1) {
      __pyx_1 = (__pyx_v_x1 >= __pyx_v_self->__pyx_base.width);
    }
    if (!__pyx_1) break;
    __pyx_1 = (__pyx_v_x1 < 0);
    if (__pyx_1) {
      __pyx_v_x1 = (__pyx_v_x1 + __pyx_v_self->__pyx_base.width);
      goto __pyx_L4;
    }
    __pyx_1 = (__pyx_v_x1 >= __pyx_v_self->__pyx_base.width);
    if (__pyx_1) {
      __pyx_v_x1 = (__pyx_v_x1 - __pyx_v_self->__pyx_base.width);
      goto __pyx_L4;
    }
    __pyx_L4:;
  }

  /* "/home/panx/ouroborus/birdcage/topology.pyx":383 */
  __pyx_r = __pyx_v_x1;
  goto __pyx_L0;

  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF((PyObject *)__pyx_v_self);
  return __pyx_r;
}

static int __pyx_f_8topology_14ToroidTopology_normal_x2(struct __pyx_obj_8topology_ToroidTopology *__pyx_v_self,int __pyx_v_x2) {
  int __pyx_r;
  int __pyx_1;
  Py_INCREF((PyObject *)__pyx_v_self);

  /* "/home/panx/ouroborus/birdcage/topology.pyx":392 */
  while (1) {
    __pyx_1 = (__pyx_v_x2 < 0);
    if (!__pyx_1) {
      __pyx_1 = (__pyx_v_x2 >= __pyx_v_self->__pyx_base.height);
    }
    if (!__pyx_1) break;
    __pyx_1 = (__pyx_v_x2 < 0);
    if (__pyx_1) {
      __pyx_v_x2 = (__pyx_v_x2 + __pyx_v_self->__pyx_base.height);
      goto __pyx_L4;
    }
    __pyx_1 = (__pyx_v_x2 >= __pyx_v_self->__pyx_base.height);
    if (__pyx_1) {
      __pyx_v_x2 = (__pyx_v_x2 - __pyx_v_self->__pyx_base.height);
      goto __pyx_L4;
    }
    __pyx_L4:;
  }

  /* "/home/panx/ouroborus/birdcage/topology.pyx":397 */
  __pyx_r = __pyx_v_x2;
  goto __pyx_L0;

  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF((PyObject *)__pyx_v_self);
  return __pyx_r;
}

static int __pyx_f_8topology_14ToroidTopology_pyx_get(struct __pyx_obj_8topology_ToroidTopology *__pyx_v_self,int __pyx_v_x1,int __pyx_v_x2) {
  int __pyx_r;
  Py_INCREF((PyObject *)__pyx_v_self);
  __pyx_r = ((__pyx_v_self->__pyx_base.cell[((struct __pyx_vtabstruct_8topology_ToroidTopology *)__pyx_v_self->__pyx_base.__pyx_base.__pyx_vtab)->__pyx_base.normal_x1(((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self),__pyx_v_x1)])[((struct __pyx_vtabstruct_8topology_ToroidTopology *)__pyx_v_self->__pyx_base.__pyx_base.__pyx_vtab)->__pyx_base.normal_x2(((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self),__pyx_v_x2)]);
  goto __pyx_L0;

  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF((PyObject *)__pyx_v_self);
  return __pyx_r;
}

static int __pyx_f_8topology_14ToroidTopology_pyx_set(struct __pyx_obj_8topology_ToroidTopology *__pyx_v_self,int __pyx_v_x1,int __pyx_v_x2,int __pyx_v_state) {
  int __pyx_r;
  Py_INCREF((PyObject *)__pyx_v_self);

  /* "/home/panx/ouroborus/birdcage/topology.pyx":418 */
  ((__pyx_v_self->__pyx_base.cell[((struct __pyx_vtabstruct_8topology_ToroidTopology *)__pyx_v_self->__pyx_base.__pyx_base.__pyx_vtab)->__pyx_base.normal_x1(((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self),__pyx_v_x1)])[((struct __pyx_vtabstruct_8topology_ToroidTopology *)__pyx_v_self->__pyx_base.__pyx_base.__pyx_vtab)->__pyx_base.normal_x2(((struct __pyx_obj_8topology_GridTopology *)__pyx_v_self),__pyx_v_x2)]) = __pyx_v_state;

  /* "/home/panx/ouroborus/birdcage/topology.pyx":419 */
  __pyx_r = 0;
  goto __pyx_L0;

  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF((PyObject *)__pyx_v_self);
  return __pyx_r;
}

static __Pyx_InternTabEntry __pyx_intern_tab[] = {
  {&__pyx_n_DimensionError, "DimensionError"},
  {&__pyx_n_E, "E"},
  {&__pyx_n_InvalidAddressError, "InvalidAddressError"},
  {&__pyx_n_SizeError, "SizeError"},
  {&__pyx_n___init__, "__init__"},
  {&__pyx_n_append, "append"},
  {&__pyx_n_exceptions_birdcage, "exceptions_birdcage"},
  {&__pyx_n_map, "map"},
  {&__pyx_n_mul, "mul"},
  {&__pyx_n_operator, "operator"},
  {&__pyx_n_random, "random"},
  {&__pyx_n_randrange, "randrange"},
  {&__pyx_n_range, "range"},
  {&__pyx_n_reduce, "reduce"},
  {&__pyx_n_set, "set"},
  {0, 0}
};

static __Pyx_StringTabEntry __pyx_string_tab[] = {
  {&__pyx_k4p, __pyx_k4, sizeof(__pyx_k4)},
  {&__pyx_k5p, __pyx_k5, sizeof(__pyx_k5)},
  {&__pyx_k6p, __pyx_k6, sizeof(__pyx_k6)},
  {0, 0, 0}
};
static struct __pyx_vtabstruct_8topology_Topology __pyx_vtable_8topology_Topology;

static PyObject *__pyx_tp_new_8topology_Topology(PyTypeObject *t, PyObject *a, PyObject *k) {
  struct __pyx_obj_8topology_Topology *p;
  PyObject *o = (*t->tp_alloc)(t, 0);
  if (!o) return 0;
  p = ((struct __pyx_obj_8topology_Topology *)o);
  *(struct __pyx_vtabstruct_8topology_Topology **)&p->__pyx_vtab = __pyx_vtabptr_8topology_Topology;
  p->size = Py_None; Py_INCREF(Py_None);
  p->zero = Py_None; Py_INCREF(Py_None);
  p->name = Py_None; Py_INCREF(Py_None);
  return o;
}

static void __pyx_tp_dealloc_8topology_Topology(PyObject *o) {
  struct __pyx_obj_8topology_Topology *p = (struct __pyx_obj_8topology_Topology *)o;
  Py_XDECREF(p->size);
  Py_XDECREF(p->zero);
  Py_XDECREF(p->name);
  (*o->ob_type->tp_free)(o);
}

static int __pyx_tp_traverse_8topology_Topology(PyObject *o, visitproc v, void *a) {
  int e;
  struct __pyx_obj_8topology_Topology *p = (struct __pyx_obj_8topology_Topology *)o;
  if (p->size) {
    e = (*v)(p->size, a); if (e) return e;
  }
  if (p->zero) {
    e = (*v)(p->zero, a); if (e) return e;
  }
  if (p->name) {
    e = (*v)(p->name, a); if (e) return e;
  }
  return 0;
}

static int __pyx_tp_clear_8topology_Topology(PyObject *o) {
  struct __pyx_obj_8topology_Topology *p = (struct __pyx_obj_8topology_Topology *)o;
  PyObject *t;
  t = p->size; 
  p->size = Py_None; Py_INCREF(Py_None);
  Py_XDECREF(t);
  t = p->zero; 
  p->zero = Py_None; Py_INCREF(Py_None);
  Py_XDECREF(t);
  t = p->name; 
  p->name = Py_None; Py_INCREF(Py_None);
  Py_XDECREF(t);
  return 0;
}

static struct PyMethodDef __pyx_methods_8topology_Topology[] = {
  {"isNormalized", (PyCFunction)__pyx_f_8topology_8Topology_isNormalized, METH_VARARGS|METH_KEYWORDS, __pyx_doc_8topology_8Topology_isNormalized},
  {"normalize", (PyCFunction)__pyx_f_8topology_8Topology_normalize, METH_VARARGS|METH_KEYWORDS, __pyx_doc_8topology_8Topology_normalize},
  {"clone", (PyCFunction)__pyx_f_8topology_8Topology_clone, METH_VARARGS|METH_KEYWORDS, __pyx_doc_8topology_8Topology_clone},
  {"get", (PyCFunction)__pyx_f_8topology_8Topology_get, METH_VARARGS|METH_KEYWORDS, __pyx_doc_8topology_8Topology_get},
  {"set", (PyCFunction)__pyx_f_8topology_8Topology_set, METH_VARARGS|METH_KEYWORDS, __pyx_doc_8topology_8Topology_set},
  {"reset", (PyCFunction)__pyx_f_8topology_8Topology_reset, METH_VARARGS|METH_KEYWORDS, __pyx_doc_8topology_8Topology_reset},
  {"center", (PyCFunction)__pyx_f_8topology_8Topology_center, METH_VARARGS|METH_KEYWORDS, __pyx_doc_8topology_8Topology_center},
  {"random", (PyCFunction)__pyx_f_8topology_8Topology_random, METH_VARARGS|METH_KEYWORDS, __pyx_doc_8topology_8Topology_random},
  {0, 0, 0, 0}
};

static PyNumberMethods __pyx_tp_as_number_Topology = {
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

static PySequenceMethods __pyx_tp_as_sequence_Topology = {
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

static PyMappingMethods __pyx_tp_as_mapping_Topology = {
  0, /*mp_length*/
  0, /*mp_subscript*/
  0, /*mp_ass_subscript*/
};

static PyBufferProcs __pyx_tp_as_buffer_Topology = {
  0, /*bf_getreadbuffer*/
  0, /*bf_getwritebuffer*/
  0, /*bf_getsegcount*/
  0, /*bf_getcharbuffer*/
};

PyTypeObject __pyx_type_8topology_Topology = {
  PyObject_HEAD_INIT(0)
  0, /*ob_size*/
  "topology.Topology", /*tp_name*/
  sizeof(struct __pyx_obj_8topology_Topology), /*tp_basicsize*/
  0, /*tp_itemsize*/
  __pyx_tp_dealloc_8topology_Topology, /*tp_dealloc*/
  0, /*tp_print*/
  0, /*tp_getattr*/
  0, /*tp_setattr*/
  0, /*tp_compare*/
  0, /*tp_repr*/
  &__pyx_tp_as_number_Topology, /*tp_as_number*/
  &__pyx_tp_as_sequence_Topology, /*tp_as_sequence*/
  &__pyx_tp_as_mapping_Topology, /*tp_as_mapping*/
  0, /*tp_hash*/
  0, /*tp_call*/
  0, /*tp_str*/
  0, /*tp_getattro*/
  0, /*tp_setattro*/
  &__pyx_tp_as_buffer_Topology, /*tp_as_buffer*/
  Py_TPFLAGS_DEFAULT|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_HAVE_GC, /*tp_flags*/
  "Abstract base class for all topologies", /*tp_doc*/
  __pyx_tp_traverse_8topology_Topology, /*tp_traverse*/
  __pyx_tp_clear_8topology_Topology, /*tp_clear*/
  0, /*tp_richcompare*/
  0, /*tp_weaklistoffset*/
  0, /*tp_iter*/
  0, /*tp_iternext*/
  __pyx_methods_8topology_Topology, /*tp_methods*/
  0, /*tp_members*/
  0, /*tp_getset*/
  0, /*tp_base*/
  0, /*tp_dict*/
  0, /*tp_descr_get*/
  0, /*tp_descr_set*/
  0, /*tp_dictoffset*/
  __pyx_f_8topology_8Topology___init__, /*tp_init*/
  0, /*tp_alloc*/
  __pyx_tp_new_8topology_Topology, /*tp_new*/
  0, /*tp_free*/
  0, /*tp_is_gc*/
  0, /*tp_bases*/
  0, /*tp_mro*/
  0, /*tp_cache*/
  0, /*tp_subclasses*/
  0, /*tp_weaklist*/
};
static struct __pyx_vtabstruct_8topology_GridTopology __pyx_vtable_8topology_GridTopology;

static PyObject *__pyx_tp_new_8topology_GridTopology(PyTypeObject *t, PyObject *a, PyObject *k) {
  struct __pyx_obj_8topology_GridTopology *p;
  PyObject *o = __pyx_ptype_8topology_Topology->tp_new(t, a, k);
  if (!o) return 0;
  p = ((struct __pyx_obj_8topology_GridTopology *)o);
  *(struct __pyx_vtabstruct_8topology_GridTopology **)&p->__pyx_base.__pyx_vtab = __pyx_vtabptr_8topology_GridTopology;
  return o;
}

static void __pyx_tp_dealloc_8topology_GridTopology(PyObject *o) {
  __pyx_ptype_8topology_Topology->tp_dealloc(o);
}

static struct PyMethodDef __pyx_methods_8topology_GridTopology[] = {
  {"clone", (PyCFunction)__pyx_f_8topology_12GridTopology_clone, METH_VARARGS|METH_KEYWORDS, __pyx_doc_8topology_12GridTopology_clone},
  {"get", (PyCFunction)__pyx_f_8topology_12GridTopology_get, METH_VARARGS|METH_KEYWORDS, __pyx_doc_8topology_12GridTopology_get},
  {"set", (PyCFunction)__pyx_f_8topology_12GridTopology_set, METH_VARARGS|METH_KEYWORDS, __pyx_doc_8topology_12GridTopology_set},
  {0, 0, 0, 0}
};

static PyNumberMethods __pyx_tp_as_number_GridTopology = {
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

static PySequenceMethods __pyx_tp_as_sequence_GridTopology = {
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

static PyMappingMethods __pyx_tp_as_mapping_GridTopology = {
  0, /*mp_length*/
  0, /*mp_subscript*/
  0, /*mp_ass_subscript*/
};

static PyBufferProcs __pyx_tp_as_buffer_GridTopology = {
  0, /*bf_getreadbuffer*/
  0, /*bf_getwritebuffer*/
  0, /*bf_getsegcount*/
  0, /*bf_getcharbuffer*/
};

PyTypeObject __pyx_type_8topology_GridTopology = {
  PyObject_HEAD_INIT(0)
  0, /*ob_size*/
  "topology.GridTopology", /*tp_name*/
  sizeof(struct __pyx_obj_8topology_GridTopology), /*tp_basicsize*/
  0, /*tp_itemsize*/
  __pyx_tp_dealloc_8topology_GridTopology, /*tp_dealloc*/
  0, /*tp_print*/
  0, /*tp_getattr*/
  0, /*tp_setattr*/
  0, /*tp_compare*/
  0, /*tp_repr*/
  &__pyx_tp_as_number_GridTopology, /*tp_as_number*/
  &__pyx_tp_as_sequence_GridTopology, /*tp_as_sequence*/
  &__pyx_tp_as_mapping_GridTopology, /*tp_as_mapping*/
  0, /*tp_hash*/
  0, /*tp_call*/
  0, /*tp_str*/
  0, /*tp_getattro*/
  0, /*tp_setattro*/
  &__pyx_tp_as_buffer_GridTopology, /*tp_as_buffer*/
  Py_TPFLAGS_DEFAULT|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_BASETYPE, /*tp_flags*/
  "A two-dimensional, bounded topology consisting of a rectangular\n     grid of cells, base class for 2D topologies", /*tp_doc*/
  0, /*tp_traverse*/
  0, /*tp_clear*/
  0, /*tp_richcompare*/
  0, /*tp_weaklistoffset*/
  0, /*tp_iter*/
  0, /*tp_iternext*/
  __pyx_methods_8topology_GridTopology, /*tp_methods*/
  0, /*tp_members*/
  0, /*tp_getset*/
  0, /*tp_base*/
  0, /*tp_dict*/
  0, /*tp_descr_get*/
  0, /*tp_descr_set*/
  0, /*tp_dictoffset*/
  __pyx_f_8topology_12GridTopology___init__, /*tp_init*/
  0, /*tp_alloc*/
  __pyx_tp_new_8topology_GridTopology, /*tp_new*/
  0, /*tp_free*/
  0, /*tp_is_gc*/
  0, /*tp_bases*/
  0, /*tp_mro*/
  0, /*tp_cache*/
  0, /*tp_subclasses*/
  0, /*tp_weaklist*/
};
static struct __pyx_vtabstruct_8topology_ToroidTopology __pyx_vtable_8topology_ToroidTopology;

static PyObject *__pyx_tp_new_8topology_ToroidTopology(PyTypeObject *t, PyObject *a, PyObject *k) {
  struct __pyx_obj_8topology_ToroidTopology *p;
  PyObject *o = __pyx_ptype_8topology_GridTopology->tp_new(t, a, k);
  if (!o) return 0;
  p = ((struct __pyx_obj_8topology_ToroidTopology *)o);
  *(struct __pyx_vtabstruct_8topology_ToroidTopology **)&p->__pyx_base.__pyx_base.__pyx_vtab = __pyx_vtabptr_8topology_ToroidTopology;
  return o;
}

static void __pyx_tp_dealloc_8topology_ToroidTopology(PyObject *o) {
  __pyx_ptype_8topology_GridTopology->tp_dealloc(o);
}

static struct PyMethodDef __pyx_methods_8topology_ToroidTopology[] = {
  {"clone", (PyCFunction)__pyx_f_8topology_14ToroidTopology_clone, METH_VARARGS|METH_KEYWORDS, __pyx_doc_8topology_14ToroidTopology_clone},
  {0, 0, 0, 0}
};

static PyNumberMethods __pyx_tp_as_number_ToroidTopology = {
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

static PySequenceMethods __pyx_tp_as_sequence_ToroidTopology = {
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

static PyMappingMethods __pyx_tp_as_mapping_ToroidTopology = {
  0, /*mp_length*/
  0, /*mp_subscript*/
  0, /*mp_ass_subscript*/
};

static PyBufferProcs __pyx_tp_as_buffer_ToroidTopology = {
  0, /*bf_getreadbuffer*/
  0, /*bf_getwritebuffer*/
  0, /*bf_getsegcount*/
  0, /*bf_getcharbuffer*/
};

PyTypeObject __pyx_type_8topology_ToroidTopology = {
  PyObject_HEAD_INIT(0)
  0, /*ob_size*/
  "topology.ToroidTopology", /*tp_name*/
  sizeof(struct __pyx_obj_8topology_ToroidTopology), /*tp_basicsize*/
  0, /*tp_itemsize*/
  __pyx_tp_dealloc_8topology_ToroidTopology, /*tp_dealloc*/
  0, /*tp_print*/
  0, /*tp_getattr*/
  0, /*tp_setattr*/
  0, /*tp_compare*/
  0, /*tp_repr*/
  &__pyx_tp_as_number_ToroidTopology, /*tp_as_number*/
  &__pyx_tp_as_sequence_ToroidTopology, /*tp_as_sequence*/
  &__pyx_tp_as_mapping_ToroidTopology, /*tp_as_mapping*/
  0, /*tp_hash*/
  0, /*tp_call*/
  0, /*tp_str*/
  0, /*tp_getattro*/
  0, /*tp_setattro*/
  &__pyx_tp_as_buffer_ToroidTopology, /*tp_as_buffer*/
  Py_TPFLAGS_DEFAULT|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_BASETYPE, /*tp_flags*/
  "A two-dimensional, unbounded topology consisting of a rectangular\n     grid of cells, where the top and bottom edges and the left and right\n     edges have been \'glued together\' (Pacman style)", /*tp_doc*/
  0, /*tp_traverse*/
  0, /*tp_clear*/
  0, /*tp_richcompare*/
  0, /*tp_weaklistoffset*/
  0, /*tp_iter*/
  0, /*tp_iternext*/
  __pyx_methods_8topology_ToroidTopology, /*tp_methods*/
  0, /*tp_members*/
  0, /*tp_getset*/
  0, /*tp_base*/
  0, /*tp_dict*/
  0, /*tp_descr_get*/
  0, /*tp_descr_set*/
  0, /*tp_dictoffset*/
  __pyx_f_8topology_14ToroidTopology___init__, /*tp_init*/
  0, /*tp_alloc*/
  __pyx_tp_new_8topology_ToroidTopology, /*tp_new*/
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

PyMODINIT_FUNC inittopology(void); /*proto*/
PyMODINIT_FUNC inittopology(void) {
  PyObject *__pyx_1 = 0;
  __pyx_init_filenames();
  __pyx_m = Py_InitModule4("topology", __pyx_methods, 0, 0, PYTHON_API_VERSION);
  if (!__pyx_m) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 24; goto __pyx_L1;};
  Py_INCREF(__pyx_m);
  __pyx_b = PyImport_AddModule("__builtin__");
  if (!__pyx_b) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 24; goto __pyx_L1;};
  if (PyObject_SetAttrString(__pyx_m, "__builtins__", __pyx_b) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 24; goto __pyx_L1;};
  if (__Pyx_InternStrings(__pyx_intern_tab) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 24; goto __pyx_L1;};
  if (__Pyx_InitStrings(__pyx_string_tab) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 24; goto __pyx_L1;};
  __pyx_vtabptr_8topology_Topology = &__pyx_vtable_8topology_Topology;
  *(void(**)(void))&__pyx_vtable_8topology_Topology.pyx_isNormalized = (void(*)(void))__pyx_f_8topology_8Topology_pyx_isNormalized;
  *(void(**)(void))&__pyx_vtable_8topology_Topology.pyx_normalize = (void(*)(void))__pyx_f_8topology_8Topology_pyx_normalize;
  __pyx_type_8topology_Topology.tp_free = _PyObject_GC_Del;
  if (PyType_Ready(&__pyx_type_8topology_Topology) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 35; goto __pyx_L1;}
  if (__Pyx_SetVtable(__pyx_type_8topology_Topology.tp_dict, __pyx_vtabptr_8topology_Topology) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 35; goto __pyx_L1;}
  if (PyObject_SetAttrString(__pyx_m, "Topology", (PyObject *)&__pyx_type_8topology_Topology) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 35; goto __pyx_L1;}
  __pyx_ptype_8topology_Topology = &__pyx_type_8topology_Topology;
  __pyx_vtabptr_8topology_GridTopology = &__pyx_vtable_8topology_GridTopology;
  __pyx_vtable_8topology_GridTopology.__pyx_base = *__pyx_vtabptr_8topology_Topology;
  *(void(**)(void))&__pyx_vtable_8topology_GridTopology.__pyx_base.pyx_normalize = (void(*)(void))__pyx_f_8topology_12GridTopology_pyx_normalize;
  *(void(**)(void))&__pyx_vtable_8topology_GridTopology.normal_x1 = (void(*)(void))__pyx_f_8topology_12GridTopology_normal_x1;
  *(void(**)(void))&__pyx_vtable_8topology_GridTopology.normal_x2 = (void(*)(void))__pyx_f_8topology_12GridTopology_normal_x2;
  *(void(**)(void))&__pyx_vtable_8topology_GridTopology.pyx_get = (void(*)(void))__pyx_f_8topology_12GridTopology_pyx_get;
  *(void(**)(void))&__pyx_vtable_8topology_GridTopology.pyx_get_nosafe = (void(*)(void))__pyx_f_8topology_12GridTopology_pyx_get_nosafe;
  *(void(**)(void))&__pyx_vtable_8topology_GridTopology.pyx_set = (void(*)(void))__pyx_f_8topology_12GridTopology_pyx_set;
  *(void(**)(void))&__pyx_vtable_8topology_GridTopology.pyx_set_nosafe = (void(*)(void))__pyx_f_8topology_12GridTopology_pyx_set_nosafe;
  __pyx_type_8topology_GridTopology.tp_base = __pyx_ptype_8topology_Topology;
  if (PyType_Ready(&__pyx_type_8topology_GridTopology) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 173; goto __pyx_L1;}
  if (__Pyx_SetVtable(__pyx_type_8topology_GridTopology.tp_dict, __pyx_vtabptr_8topology_GridTopology) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 173; goto __pyx_L1;}
  if (PyObject_SetAttrString(__pyx_m, "GridTopology", (PyObject *)&__pyx_type_8topology_GridTopology) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 173; goto __pyx_L1;}
  __pyx_ptype_8topology_GridTopology = &__pyx_type_8topology_GridTopology;
  __pyx_vtabptr_8topology_ToroidTopology = &__pyx_vtable_8topology_ToroidTopology;
  __pyx_vtable_8topology_ToroidTopology.__pyx_base = *__pyx_vtabptr_8topology_GridTopology;
  *(void(**)(void))&__pyx_vtable_8topology_ToroidTopology.__pyx_base.__pyx_base.pyx_normalize = (void(*)(void))__pyx_f_8topology_14ToroidTopology_pyx_normalize;
  *(void(**)(void))&__pyx_vtable_8topology_ToroidTopology.__pyx_base.normal_x1 = (void(*)(void))__pyx_f_8topology_14ToroidTopology_normal_x1;
  *(void(**)(void))&__pyx_vtable_8topology_ToroidTopology.__pyx_base.normal_x2 = (void(*)(void))__pyx_f_8topology_14ToroidTopology_normal_x2;
  *(void(**)(void))&__pyx_vtable_8topology_ToroidTopology.__pyx_base.pyx_get = (void(*)(void))__pyx_f_8topology_14ToroidTopology_pyx_get;
  *(void(**)(void))&__pyx_vtable_8topology_ToroidTopology.__pyx_base.pyx_set = (void(*)(void))__pyx_f_8topology_14ToroidTopology_pyx_set;
  __pyx_type_8topology_ToroidTopology.tp_base = __pyx_ptype_8topology_GridTopology;
  if (PyType_Ready(&__pyx_type_8topology_ToroidTopology) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 334; goto __pyx_L1;}
  if (__Pyx_SetVtable(__pyx_type_8topology_ToroidTopology.tp_dict, __pyx_vtabptr_8topology_ToroidTopology) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 334; goto __pyx_L1;}
  if (PyObject_SetAttrString(__pyx_m, "ToroidTopology", (PyObject *)&__pyx_type_8topology_ToroidTopology) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 334; goto __pyx_L1;}
  __pyx_ptype_8topology_ToroidTopology = &__pyx_type_8topology_ToroidTopology;

  /* "/home/panx/ouroborus/birdcage/topology.pyx":24 */
  __pyx_1 = __Pyx_Import(__pyx_n_exceptions_birdcage, 0); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 24; goto __pyx_L1;}
  if (PyObject_SetAttr(__pyx_m, __pyx_n_E, __pyx_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 24; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;

  /* "/home/panx/ouroborus/birdcage/topology.pyx":25 */
  __pyx_1 = __Pyx_Import(__pyx_n_operator, 0); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 25; goto __pyx_L1;}
  if (PyObject_SetAttr(__pyx_m, __pyx_n_operator, __pyx_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 25; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;

  /* "/home/panx/ouroborus/birdcage/topology.pyx":26 */
  __pyx_1 = __Pyx_Import(__pyx_n_random, 0); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 26; goto __pyx_L1;}
  if (PyObject_SetAttr(__pyx_m, __pyx_n_random, __pyx_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 26; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;

  /* "/home/panx/ouroborus/birdcage/topology.pyx":410 */
  return;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  __Pyx_AddTraceback("topology");
}

static char *__pyx_filenames[] = {
  "topology.pyx",
};

/* Runtime support code */

static void __pyx_init_filenames(void) {
  __pyx_f = __pyx_filenames;
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

static void __Pyx_WriteUnraisable(char *name) {
    PyObject *old_exc, *old_val, *old_tb;
    PyObject *ctx;
    PyErr_Fetch(&old_exc, &old_val, &old_tb);
    ctx = PyString_FromString(name);
    PyErr_Restore(old_exc, old_val, old_tb);
    if (!ctx)
        ctx = Py_None;
    PyErr_WriteUnraisable(ctx);
}

static void __Pyx_UnpackError(void) {
    PyErr_SetString(PyExc_ValueError, "unpack sequence of wrong size");
}

static PyObject *__Pyx_UnpackItem(PyObject *iter) {
    PyObject *item;
    if (!(item = PyIter_Next(iter))) {
        if (!PyErr_Occurred())
            __Pyx_UnpackError();
    }
    return item;
}

static int __Pyx_EndUnpack(PyObject *iter) {
    PyObject *item;
    if ((item = PyIter_Next(iter))) {
        Py_DECREF(item);
        __Pyx_UnpackError();
        return -1;
    }
    else if (!PyErr_Occurred())
        return 0;
    else
        return -1;
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

static int __Pyx_SetItemInt(PyObject *o, Py_ssize_t i, PyObject *v) {
    PyTypeObject *t = o->ob_type;
    int r;
    if (t->tp_as_sequence && t->tp_as_sequence->sq_item)
        r = PySequence_SetItem(o, i, v);
    else {
        PyObject *j = PyInt_FromLong(i);
        if (!j)
            return -1;
        r = PyObject_SetItem(o, j, v);
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
