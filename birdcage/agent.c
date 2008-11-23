/* 0.9.7.2 on Thu Sep 25 19:21:12 2008 */

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

/* Declarations from genome */

struct __pyx_obj_6genome_Genome {
  PyObject_HEAD
  struct __pyx_vtabstruct_6genome_Genome *__pyx_vtab;
  PyObject *text;
  PyObject *table;
  int wordlength;
};


struct __pyx_vtabstruct_6genome_Genome {
  PyObject *(*pyx_readWord)(struct __pyx_obj_6genome_Genome *,int);
  PyObject *(*pyx_decode)(struct __pyx_obj_6genome_Genome *,PyObject *);
  PyObject *(*pyx_parse)(struct __pyx_obj_6genome_Genome *);
};
static struct __pyx_vtabstruct_6genome_Genome *__pyx_vtabptr_6genome_Genome;

static PyTypeObject *__pyx_ptype_6genome_Genome = 0;

/* Declarations from agent */

struct __pyx_obj_5agent_Agent {
  PyObject_HEAD
  struct __pyx_vtabstruct_5agent_Agent *__pyx_vtab;
  struct __pyx_obj_12neighborhood_Neighborhood_2D *corporality;
  struct __pyx_obj_12neighborhood_Neighborhood_2D *sensoriality;
  struct __pyx_obj_8topology_GridTopology *topology;
  int prana;
  int mana;
  PyObject *code;
  PyObject *name;
  PyObject *moira;
};

struct __pyx_obj_5agent_Agent_2D {
  struct __pyx_obj_5agent_Agent __pyx_base;
  int directions;
  int facing;
  int x1;
  int x2;
};


struct __pyx_vtabstruct_5agent_Agent {
  int (*pyx_isAlive)(struct __pyx_obj_5agent_Agent *);
  int (*pyx_tellPrana)(struct __pyx_obj_5agent_Agent *);
  void (*pyx_gainPrana)(struct __pyx_obj_5agent_Agent *,int);
  void (*pyx_losePrana)(struct __pyx_obj_5agent_Agent *,int);
  void (*pyx_zeroPrana)(struct __pyx_obj_5agent_Agent *);
  void (*pyx_update)(struct __pyx_obj_5agent_Agent *);
};
static struct __pyx_vtabstruct_5agent_Agent *__pyx_vtabptr_5agent_Agent;


struct __pyx_vtabstruct_5agent_Agent_2D {
  struct __pyx_vtabstruct_5agent_Agent __pyx_base;
  void (*pyx_move)(struct __pyx_obj_5agent_Agent_2D *,int,int);
  int (*pyx_changeFacing)(struct __pyx_obj_5agent_Agent_2D *,int);
  int (*pyx_advance)(struct __pyx_obj_5agent_Agent_2D *);
  int (*pyx_eatMana)(struct __pyx_obj_5agent_Agent_2D *);
};
static struct __pyx_vtabstruct_5agent_Agent_2D *__pyx_vtabptr_5agent_Agent_2D;

static PyTypeObject *__pyx_ptype_5agent_Agent = 0;
static PyTypeObject *__pyx_ptype_5agent_Agent_2D = 0;


/* Implementation of agent */


static PyObject *__pyx_n_exceptions_birdcage;
static PyObject *__pyx_n_E;

static PyObject *__pyx_n_ConflictingTopologyError;

static PyObject *__pyx_k2p;

static char __pyx_k2[] = "Abstract Agent";

static int __pyx_f_5agent_5Agent___init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static int __pyx_f_5agent_5Agent___init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_code = 0;
  struct __pyx_obj_12neighborhood_Neighborhood_2D *__pyx_v_corporality = 0;
  struct __pyx_obj_12neighborhood_Neighborhood_2D *__pyx_v_sensoriality = 0;
  int __pyx_v_prana;
  int __pyx_v_mana;
  PyObject *__pyx_v_address = 0;
  int __pyx_r;
  int __pyx_1;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  PyObject *__pyx_4 = 0;
  static char *__pyx_argnames[] = {"code","corporality","sensoriality","prana","mana","address",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "OOOiiO", __pyx_argnames, &__pyx_v_code, &__pyx_v_corporality, &__pyx_v_sensoriality, &__pyx_v_prana, &__pyx_v_mana, &__pyx_v_address)) return -1;
  Py_INCREF(__pyx_v_self);
  Py_INCREF(__pyx_v_code);
  Py_INCREF(__pyx_v_corporality);
  Py_INCREF(__pyx_v_sensoriality);
  Py_INCREF(__pyx_v_address);
  if (!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_corporality), __pyx_ptype_12neighborhood_Neighborhood_2D, 1, "corporality")) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 36; goto __pyx_L1;}
  if (!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_sensoriality), __pyx_ptype_12neighborhood_Neighborhood_2D, 1, "sensoriality")) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 36; goto __pyx_L1;}

  /* "/home/panx/ouroborus/birdcage/agent.pyx":48 */
  Py_INCREF(__pyx_v_code);
  Py_DECREF(((struct __pyx_obj_5agent_Agent *)__pyx_v_self)->code);
  ((struct __pyx_obj_5agent_Agent *)__pyx_v_self)->code = __pyx_v_code;

  /* "/home/panx/ouroborus/birdcage/agent.pyx":49 */
  Py_INCREF(((PyObject *)__pyx_v_corporality));
  Py_DECREF(((PyObject *)((struct __pyx_obj_5agent_Agent *)__pyx_v_self)->corporality));
  ((struct __pyx_obj_5agent_Agent *)__pyx_v_self)->corporality = __pyx_v_corporality;

  /* "/home/panx/ouroborus/birdcage/agent.pyx":50 */
  Py_INCREF(((PyObject *)__pyx_v_sensoriality));
  Py_DECREF(((PyObject *)((struct __pyx_obj_5agent_Agent *)__pyx_v_self)->sensoriality));
  ((struct __pyx_obj_5agent_Agent *)__pyx_v_self)->sensoriality = __pyx_v_sensoriality;

  /* "/home/panx/ouroborus/birdcage/agent.pyx":52 */
  if (PyObject_Cmp(((PyObject *)((struct __pyx_obj_5agent_Agent *)__pyx_v_self)->corporality->topology), ((PyObject *)((struct __pyx_obj_5agent_Agent *)__pyx_v_self)->sensoriality->topology), &__pyx_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 52; goto __pyx_L1;}
  __pyx_1 = __pyx_1 != 0;
  if (__pyx_1) {
    __pyx_2 = __Pyx_GetName(__pyx_m, __pyx_n_E); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 53; goto __pyx_L1;}
    __pyx_3 = PyObject_GetAttr(__pyx_2, __pyx_n_ConflictingTopologyError); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 53; goto __pyx_L1;}
    Py_DECREF(__pyx_2); __pyx_2 = 0;
    __pyx_2 = PyTuple_New(2); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 53; goto __pyx_L1;}
    Py_INCREF(((struct __pyx_obj_5agent_Agent *)__pyx_v_self)->corporality->topology->__pyx_base.name);
    PyTuple_SET_ITEM(__pyx_2, 0, ((struct __pyx_obj_5agent_Agent *)__pyx_v_self)->corporality->topology->__pyx_base.name);
    Py_INCREF(((struct __pyx_obj_5agent_Agent *)__pyx_v_self)->sensoriality->topology->__pyx_base.name);
    PyTuple_SET_ITEM(__pyx_2, 1, ((struct __pyx_obj_5agent_Agent *)__pyx_v_self)->sensoriality->topology->__pyx_base.name);
    __pyx_4 = PyObject_CallObject(__pyx_3, __pyx_2); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 53; goto __pyx_L1;}
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    Py_DECREF(__pyx_2); __pyx_2 = 0;
    __Pyx_Raise(__pyx_4, 0, 0);
    Py_DECREF(__pyx_4); __pyx_4 = 0;
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 53; goto __pyx_L1;}
    goto __pyx_L2;
  }
  __pyx_L2:;

  /* "/home/panx/ouroborus/birdcage/agent.pyx":55 */
  Py_INCREF(((PyObject *)((struct __pyx_obj_5agent_Agent *)__pyx_v_self)->corporality->topology));
  Py_DECREF(((PyObject *)((struct __pyx_obj_5agent_Agent *)__pyx_v_self)->topology));
  ((struct __pyx_obj_5agent_Agent *)__pyx_v_self)->topology = ((struct __pyx_obj_5agent_Agent *)__pyx_v_self)->corporality->topology;

  /* "/home/panx/ouroborus/birdcage/agent.pyx":57 */
  Py_INCREF(Py_None);
  Py_DECREF(((struct __pyx_obj_5agent_Agent *)__pyx_v_self)->moira);
  ((struct __pyx_obj_5agent_Agent *)__pyx_v_self)->moira = Py_None;

  /* "/home/panx/ouroborus/birdcage/agent.pyx":59 */
  ((struct __pyx_obj_5agent_Agent *)__pyx_v_self)->prana = __pyx_v_prana;

  /* "/home/panx/ouroborus/birdcage/agent.pyx":60 */
  ((struct __pyx_obj_5agent_Agent *)__pyx_v_self)->mana = __pyx_v_mana;

  /* "/home/panx/ouroborus/birdcage/agent.pyx":61 */
  Py_INCREF(__pyx_k2p);
  Py_DECREF(((struct __pyx_obj_5agent_Agent *)__pyx_v_self)->name);
  ((struct __pyx_obj_5agent_Agent *)__pyx_v_self)->name = __pyx_k2p;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  Py_XDECREF(__pyx_4);
  __Pyx_AddTraceback("agent.Agent.__init__");
  __pyx_r = -1;
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  Py_DECREF(__pyx_v_code);
  Py_DECREF(__pyx_v_corporality);
  Py_DECREF(__pyx_v_sensoriality);
  Py_DECREF(__pyx_v_address);
  return __pyx_r;
}

static PyObject *__pyx_f_5agent_5Agent_isAlive(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_5agent_5Agent_isAlive[] = "Return True if agent has positive prana, False otherwise\n\n          return -->> Boolean";
static PyObject *__pyx_f_5agent_5Agent_isAlive(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_r;
  PyObject *__pyx_1 = 0;
  static char *__pyx_argnames[] = {0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "", __pyx_argnames)) return 0;
  Py_INCREF(__pyx_v_self);
  __pyx_1 = PyInt_FromLong((((struct __pyx_obj_5agent_Agent *)__pyx_v_self)->prana > 0)); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 69; goto __pyx_L1;}
  __pyx_r = __pyx_1;
  __pyx_1 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  __Pyx_AddTraceback("agent.Agent.isAlive");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  return __pyx_r;
}

static int __pyx_f_5agent_5Agent_pyx_isAlive(struct __pyx_obj_5agent_Agent *__pyx_v_self) {
  int __pyx_r;
  Py_INCREF(__pyx_v_self);
  __pyx_r = (__pyx_v_self->prana > 0);
  goto __pyx_L0;

  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  return __pyx_r;
}

static PyObject *__pyx_f_5agent_5Agent_tellPrana(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_5agent_5Agent_tellPrana[] = "Return the amount of prana the Agent has\n\n          return -->> the Agent\'s prana as an integer value";
static PyObject *__pyx_f_5agent_5Agent_tellPrana(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_r;
  PyObject *__pyx_1 = 0;
  static char *__pyx_argnames[] = {0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "", __pyx_argnames)) return 0;
  Py_INCREF(__pyx_v_self);
  __pyx_1 = PyInt_FromLong(((struct __pyx_vtabstruct_5agent_Agent *)((struct __pyx_obj_5agent_Agent *)__pyx_v_self)->__pyx_vtab)->pyx_tellPrana(((struct __pyx_obj_5agent_Agent *)__pyx_v_self))); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 85; goto __pyx_L1;}
  __pyx_r = __pyx_1;
  __pyx_1 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  __Pyx_AddTraceback("agent.Agent.tellPrana");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  return __pyx_r;
}

static int __pyx_f_5agent_5Agent_pyx_tellPrana(struct __pyx_obj_5agent_Agent *__pyx_v_self) {
  int __pyx_r;
  Py_INCREF(__pyx_v_self);
  __pyx_r = __pyx_v_self->prana;
  goto __pyx_L0;

  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_self);
  return __pyx_r;
}

static PyObject *__pyx_f_5agent_5Agent_gainPrana(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_5agent_5Agent_gainPrana[] = "Increase Agent\'s prana by a given amount)\n\n          amount ---> the integer increase of prana\n          return -->> None";
static PyObject *__pyx_f_5agent_5Agent_gainPrana(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  int __pyx_v_amount;
  PyObject *__pyx_r;
  static char *__pyx_argnames[] = {"amount",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "i", __pyx_argnames, &__pyx_v_amount)) return 0;
  Py_INCREF(__pyx_v_self);
  ((struct __pyx_vtabstruct_5agent_Agent *)((struct __pyx_obj_5agent_Agent *)__pyx_v_self)->__pyx_vtab)->pyx_gainPrana(((struct __pyx_obj_5agent_Agent *)__pyx_v_self),__pyx_v_amount);

  __pyx_r = Py_None; Py_INCREF(Py_None);
  Py_DECREF(__pyx_v_self);
  return __pyx_r;
}

static void __pyx_f_5agent_5Agent_pyx_gainPrana(struct __pyx_obj_5agent_Agent *__pyx_v_self,int __pyx_v_amount) {
  Py_INCREF(__pyx_v_self);
  __pyx_v_self->prana = (__pyx_v_self->prana + __pyx_v_amount);

  Py_DECREF(__pyx_v_self);
}

static PyObject *__pyx_f_5agent_5Agent_losePrana(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_5agent_5Agent_losePrana[] = "Decrease Agent\'s prana by a given amount)\n\n          amount ---> the integer decrease of prana\n          return -->> None";
static PyObject *__pyx_f_5agent_5Agent_losePrana(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  int __pyx_v_amount;
  PyObject *__pyx_r;
  static char *__pyx_argnames[] = {"amount",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "i", __pyx_argnames, &__pyx_v_amount)) return 0;
  Py_INCREF(__pyx_v_self);
  ((struct __pyx_vtabstruct_5agent_Agent *)((struct __pyx_obj_5agent_Agent *)__pyx_v_self)->__pyx_vtab)->pyx_losePrana(((struct __pyx_obj_5agent_Agent *)__pyx_v_self),__pyx_v_amount);

  __pyx_r = Py_None; Py_INCREF(Py_None);
  Py_DECREF(__pyx_v_self);
  return __pyx_r;
}

static void __pyx_f_5agent_5Agent_pyx_losePrana(struct __pyx_obj_5agent_Agent *__pyx_v_self,int __pyx_v_amount) {
  int __pyx_1;
  Py_INCREF(__pyx_v_self);

  /* "/home/panx/ouroborus/birdcage/agent.pyx":129 */
  __pyx_v_self->prana = (__pyx_v_self->prana - __pyx_v_amount);

  /* "/home/panx/ouroborus/birdcage/agent.pyx":130 */
  __pyx_1 = (__pyx_v_self->prana < 0);
  if (__pyx_1) {
    __pyx_v_self->prana = 0;
    goto __pyx_L2;
  }
  __pyx_L2:;

  Py_DECREF(__pyx_v_self);
}

static PyObject *__pyx_f_5agent_5Agent_zeroPrana(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_5agent_5Agent_zeroPrana[] = "Lose all prana; set it to zero\n\n          return -->> None";
static PyObject *__pyx_f_5agent_5Agent_zeroPrana(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_r;
  static char *__pyx_argnames[] = {0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "", __pyx_argnames)) return 0;
  Py_INCREF(__pyx_v_self);
  ((struct __pyx_vtabstruct_5agent_Agent *)((struct __pyx_obj_5agent_Agent *)__pyx_v_self)->__pyx_vtab)->pyx_zeroPrana(((struct __pyx_obj_5agent_Agent *)__pyx_v_self));

  __pyx_r = Py_None; Py_INCREF(Py_None);
  Py_DECREF(__pyx_v_self);
  return __pyx_r;
}

static void __pyx_f_5agent_5Agent_pyx_zeroPrana(struct __pyx_obj_5agent_Agent *__pyx_v_self) {
  Py_INCREF(__pyx_v_self);
  __pyx_v_self->prana = 0;

  Py_DECREF(__pyx_v_self);
}

static PyObject *__pyx_f_5agent_5Agent_update(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_5agent_5Agent_update[] = "The agent does its thing, whatever it is\n\n          return -->> None";
static PyObject *__pyx_f_5agent_5Agent_update(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_r;
  static char *__pyx_argnames[] = {0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "", __pyx_argnames)) return 0;
  Py_INCREF(__pyx_v_self);
  ((struct __pyx_vtabstruct_5agent_Agent *)((struct __pyx_obj_5agent_Agent *)__pyx_v_self)->__pyx_vtab)->pyx_update(((struct __pyx_obj_5agent_Agent *)__pyx_v_self));

  __pyx_r = Py_None; Py_INCREF(Py_None);
  Py_DECREF(__pyx_v_self);
  return __pyx_r;
}

static void __pyx_f_5agent_5Agent_pyx_update(struct __pyx_obj_5agent_Agent *__pyx_v_self) {
  Py_INCREF(__pyx_v_self);
  __pyx_v_self->prana = (__pyx_v_self->prana - 1);

  Py_DECREF(__pyx_v_self);
}

static PyObject *__pyx_n___init__;
static PyObject *__pyx_n_normalize;

static PyObject *__pyx_k3p;

static char __pyx_k3[] = "Agent 2-D";

static int __pyx_f_5agent_8Agent_2D___init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static int __pyx_f_5agent_8Agent_2D___init__(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_code = 0;
  struct __pyx_obj_12neighborhood_Neighborhood_2D *__pyx_v_corporality = 0;
  struct __pyx_obj_12neighborhood_Neighborhood_2D *__pyx_v_sensoriality = 0;
  int __pyx_v_prana;
  int __pyx_v_mana;
  PyObject *__pyx_v_address = 0;
  int __pyx_r;
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  PyObject *__pyx_4 = 0;
  int __pyx_5;
  int __pyx_6;
  static char *__pyx_argnames[] = {"code","corporality","sensoriality","prana","mana","address",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "OOOiiO", __pyx_argnames, &__pyx_v_code, &__pyx_v_corporality, &__pyx_v_sensoriality, &__pyx_v_prana, &__pyx_v_mana, &__pyx_v_address)) return -1;
  Py_INCREF((PyObject *)__pyx_v_self);
  Py_INCREF(__pyx_v_code);
  Py_INCREF(__pyx_v_corporality);
  Py_INCREF(__pyx_v_sensoriality);
  Py_INCREF(__pyx_v_address);
  if (!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_corporality), __pyx_ptype_12neighborhood_Neighborhood_2D, 1, "corporality")) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 172; goto __pyx_L1;}
  if (!__Pyx_ArgTypeTest(((PyObject *)__pyx_v_sensoriality), __pyx_ptype_12neighborhood_Neighborhood_2D, 1, "sensoriality")) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 172; goto __pyx_L1;}

  /* "/home/panx/ouroborus/birdcage/agent.pyx":184 */
  __pyx_1 = PyObject_GetAttr(((PyObject *)__pyx_ptype_5agent_Agent), __pyx_n___init__); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 184; goto __pyx_L1;}
  __pyx_2 = PyInt_FromLong(__pyx_v_prana); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 184; goto __pyx_L1;}
  __pyx_3 = PyInt_FromLong(__pyx_v_mana); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 184; goto __pyx_L1;}
  __pyx_4 = PyTuple_New(7); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 184; goto __pyx_L1;}
  Py_INCREF(__pyx_v_self);
  PyTuple_SET_ITEM(__pyx_4, 0, __pyx_v_self);
  Py_INCREF(__pyx_v_code);
  PyTuple_SET_ITEM(__pyx_4, 1, __pyx_v_code);
  Py_INCREF(((PyObject *)__pyx_v_corporality));
  PyTuple_SET_ITEM(__pyx_4, 2, ((PyObject *)__pyx_v_corporality));
  Py_INCREF(((PyObject *)__pyx_v_sensoriality));
  PyTuple_SET_ITEM(__pyx_4, 3, ((PyObject *)__pyx_v_sensoriality));
  PyTuple_SET_ITEM(__pyx_4, 4, __pyx_2);
  PyTuple_SET_ITEM(__pyx_4, 5, __pyx_3);
  Py_INCREF(__pyx_v_address);
  PyTuple_SET_ITEM(__pyx_4, 6, __pyx_v_address);
  __pyx_2 = 0;
  __pyx_3 = 0;
  __pyx_2 = PyObject_CallObject(__pyx_1, __pyx_4); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 184; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  Py_DECREF(__pyx_4); __pyx_4 = 0;
  Py_DECREF(__pyx_2); __pyx_2 = 0;

  /* "/home/panx/ouroborus/birdcage/agent.pyx":186 */
  __pyx_3 = PyObject_GetAttr(((PyObject *)((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->__pyx_base.topology), __pyx_n_normalize); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 186; goto __pyx_L1;}
  __pyx_1 = PyTuple_New(1); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 186; goto __pyx_L1;}
  Py_INCREF(__pyx_v_address);
  PyTuple_SET_ITEM(__pyx_1, 0, __pyx_v_address);
  __pyx_4 = PyObject_CallObject(__pyx_3, __pyx_1); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 186; goto __pyx_L1;}
  Py_DECREF(__pyx_3); __pyx_3 = 0;
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  Py_DECREF(__pyx_v_address);
  __pyx_v_address = __pyx_4;
  __pyx_4 = 0;

  /* "/home/panx/ouroborus/birdcage/agent.pyx":187 */
  __pyx_2 = __Pyx_GetItemInt(__pyx_v_address, 0); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 187; goto __pyx_L1;}
  __pyx_5 = PyInt_AsLong(__pyx_2); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 187; goto __pyx_L1;}
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  __pyx_3 = __Pyx_GetItemInt(__pyx_v_address, 1); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 187; goto __pyx_L1;}
  __pyx_6 = PyInt_AsLong(__pyx_3); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 187; goto __pyx_L1;}
  Py_DECREF(__pyx_3); __pyx_3 = 0;
  ((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->x1 = __pyx_5;
  ((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->x2 = __pyx_6;

  /* "/home/panx/ouroborus/birdcage/agent.pyx":188 */
  ((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->directions = (((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->__pyx_base.sensoriality->neighbors + 1);

  /* "/home/panx/ouroborus/birdcage/agent.pyx":189 */
  ((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->facing = 0;

  /* "/home/panx/ouroborus/birdcage/agent.pyx":190 */
  Py_INCREF(__pyx_k3p);
  Py_DECREF(((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->__pyx_base.name);
  ((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->__pyx_base.name = __pyx_k3p;

  __pyx_r = 0;
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  Py_XDECREF(__pyx_4);
  __Pyx_AddTraceback("agent.Agent_2D.__init__");
  __pyx_r = -1;
  __pyx_L0:;
  Py_DECREF((PyObject *)__pyx_v_self);
  Py_DECREF(__pyx_v_code);
  Py_DECREF(__pyx_v_corporality);
  Py_DECREF(__pyx_v_sensoriality);
  Py_DECREF(__pyx_v_address);
  return __pyx_r;
}

static PyObject *__pyx_f_5agent_8Agent_2D_tellAddress(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_5agent_8Agent_2D_tellAddress[] = "Return the agent\'s address on the grid\n\n          return -->> a Python 2-tuple";
static PyObject *__pyx_f_5agent_8Agent_2D_tellAddress(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_r;
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  static char *__pyx_argnames[] = {0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "", __pyx_argnames)) return 0;
  Py_INCREF((PyObject *)__pyx_v_self);
  __pyx_1 = PyInt_FromLong(((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->x1); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 198; goto __pyx_L1;}
  __pyx_2 = PyInt_FromLong(((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->x2); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 198; goto __pyx_L1;}
  __pyx_3 = PyTuple_New(2); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 198; goto __pyx_L1;}
  PyTuple_SET_ITEM(__pyx_3, 0, __pyx_1);
  PyTuple_SET_ITEM(__pyx_3, 1, __pyx_2);
  __pyx_1 = 0;
  __pyx_2 = 0;
  __pyx_r = __pyx_3;
  __pyx_3 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  __Pyx_AddTraceback("agent.Agent_2D.tellAddress");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF((PyObject *)__pyx_v_self);
  return __pyx_r;
}

static PyObject *__pyx_n_listNeighbors;
static PyObject *__pyx_n_append;

static PyObject *__pyx_f_5agent_8Agent_2D_tellCorporality(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_5agent_8Agent_2D_tellCorporality[] = "Return a list with the grid addresses covered\n          by the agent\'s corporality\n\n          return -->> a Python list of 2-tuples";
static PyObject *__pyx_f_5agent_8Agent_2D_tellCorporality(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_address;
  PyObject *__pyx_v_addresses;
  PyObject *__pyx_v_neighbor;
  PyObject *__pyx_v_neighbors;
  PyObject *__pyx_r;
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  int __pyx_4;
  PyObject *__pyx_5 = 0;
  static char *__pyx_argnames[] = {0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "", __pyx_argnames)) return 0;
  Py_INCREF((PyObject *)__pyx_v_self);
  __pyx_v_address = Py_None; Py_INCREF(Py_None);
  __pyx_v_addresses = Py_None; Py_INCREF(Py_None);
  __pyx_v_neighbor = Py_None; Py_INCREF(Py_None);
  __pyx_v_neighbors = Py_None; Py_INCREF(Py_None);

  /* "/home/panx/ouroborus/birdcage/agent.pyx":209 */
  __pyx_1 = PyInt_FromLong(((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->x1); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 209; goto __pyx_L1;}
  __pyx_2 = PyInt_FromLong(((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->x2); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 209; goto __pyx_L1;}
  __pyx_3 = PyTuple_New(2); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 209; goto __pyx_L1;}
  PyTuple_SET_ITEM(__pyx_3, 0, __pyx_1);
  PyTuple_SET_ITEM(__pyx_3, 1, __pyx_2);
  __pyx_1 = 0;
  __pyx_2 = 0;
  Py_DECREF(__pyx_v_address);
  __pyx_v_address = __pyx_3;
  __pyx_3 = 0;

  /* "/home/panx/ouroborus/birdcage/agent.pyx":210 */
  __pyx_1 = PyList_New(0); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 210; goto __pyx_L1;}
  Py_DECREF(__pyx_v_addresses);
  __pyx_v_addresses = __pyx_1;
  __pyx_1 = 0;

  /* "/home/panx/ouroborus/birdcage/agent.pyx":211 */
  __pyx_2 = PyObject_GetAttr(((PyObject *)((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->__pyx_base.corporality), __pyx_n_listNeighbors); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 211; goto __pyx_L1;}
  __pyx_3 = PyTuple_New(1); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 211; goto __pyx_L1;}
  Py_INCREF(__pyx_v_address);
  PyTuple_SET_ITEM(__pyx_3, 0, __pyx_v_address);
  __pyx_1 = PyObject_CallObject(__pyx_2, __pyx_3); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 211; goto __pyx_L1;}
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  Py_DECREF(__pyx_3); __pyx_3 = 0;
  Py_DECREF(__pyx_v_neighbors);
  __pyx_v_neighbors = __pyx_1;
  __pyx_1 = 0;

  /* "/home/panx/ouroborus/birdcage/agent.pyx":212 */
  __pyx_4 = PySequence_Contains(__pyx_v_neighbors, __pyx_v_address); if (__pyx_4 < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 212; goto __pyx_L1;}
  __pyx_4 = !__pyx_4;
  if (__pyx_4) {
    __pyx_2 = PyObject_GetAttr(__pyx_v_addresses, __pyx_n_append); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 213; goto __pyx_L1;}
    __pyx_3 = PyTuple_New(1); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 213; goto __pyx_L1;}
    Py_INCREF(__pyx_v_address);
    PyTuple_SET_ITEM(__pyx_3, 0, __pyx_v_address);
    __pyx_1 = PyObject_CallObject(__pyx_2, __pyx_3); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 213; goto __pyx_L1;}
    Py_DECREF(__pyx_2); __pyx_2 = 0;
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    Py_DECREF(__pyx_1); __pyx_1 = 0;
    goto __pyx_L2;
  }
  __pyx_L2:;

  /* "/home/panx/ouroborus/birdcage/agent.pyx":214 */
  __pyx_2 = PyObject_GetIter(__pyx_v_neighbors); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 214; goto __pyx_L1;}
  for (;;) {
    __pyx_3 = PyIter_Next(__pyx_2);
    if (!__pyx_3) {
      if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 214; goto __pyx_L1;}
      break;
    }
    Py_DECREF(__pyx_v_neighbor);
    __pyx_v_neighbor = __pyx_3;
    __pyx_3 = 0;
    __pyx_1 = PyObject_GetAttr(__pyx_v_addresses, __pyx_n_append); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 215; goto __pyx_L1;}
    __pyx_3 = PyTuple_New(1); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 215; goto __pyx_L1;}
    Py_INCREF(__pyx_v_neighbor);
    PyTuple_SET_ITEM(__pyx_3, 0, __pyx_v_neighbor);
    __pyx_5 = PyObject_CallObject(__pyx_1, __pyx_3); if (!__pyx_5) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 215; goto __pyx_L1;}
    Py_DECREF(__pyx_1); __pyx_1 = 0;
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    Py_DECREF(__pyx_5); __pyx_5 = 0;
  }
  Py_DECREF(__pyx_2); __pyx_2 = 0;

  /* "/home/panx/ouroborus/birdcage/agent.pyx":216 */
  Py_INCREF(__pyx_v_addresses);
  __pyx_r = __pyx_v_addresses;
  goto __pyx_L0;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  Py_XDECREF(__pyx_5);
  __Pyx_AddTraceback("agent.Agent_2D.tellCorporality");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_address);
  Py_DECREF(__pyx_v_addresses);
  Py_DECREF(__pyx_v_neighbor);
  Py_DECREF(__pyx_v_neighbors);
  Py_DECREF((PyObject *)__pyx_v_self);
  return __pyx_r;
}

static PyObject *__pyx_n_InvalidAddressError;

static PyObject *__pyx_f_5agent_8Agent_2D_move(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_5agent_8Agent_2D_move[] = "Move the agent to a new address\n\n          address ---> a Python 2-tuple, an address on the grid";
static PyObject *__pyx_f_5agent_8Agent_2D_move(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
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

  /* "/home/panx/ouroborus/birdcage/agent.pyx":224 */
  __pyx_1 = PyObject_Length(__pyx_v_address); if (__pyx_1 == -1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 224; goto __pyx_L1;}
  __pyx_2 = (!(__pyx_1 == 2));
  if (__pyx_2) {
    __pyx_3 = __Pyx_GetName(__pyx_m, __pyx_n_E); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 225; goto __pyx_L1;}
    __pyx_4 = PyObject_GetAttr(__pyx_3, __pyx_n_InvalidAddressError); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 225; goto __pyx_L1;}
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    __pyx_3 = PyTuple_New(2); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 225; goto __pyx_L1;}
    Py_INCREF(__pyx_v_address);
    PyTuple_SET_ITEM(__pyx_3, 0, __pyx_v_address);
    Py_INCREF(((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->__pyx_base.topology->__pyx_base.name);
    PyTuple_SET_ITEM(__pyx_3, 1, ((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->__pyx_base.topology->__pyx_base.name);
    __pyx_5 = PyObject_CallObject(__pyx_4, __pyx_3); if (!__pyx_5) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 225; goto __pyx_L1;}
    Py_DECREF(__pyx_4); __pyx_4 = 0;
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    __Pyx_Raise(__pyx_5, 0, 0);
    Py_DECREF(__pyx_5); __pyx_5 = 0;
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 225; goto __pyx_L1;}
    goto __pyx_L2;
  }
  __pyx_L2:;

  /* "/home/panx/ouroborus/birdcage/agent.pyx":227 */
  __pyx_4 = PyObject_GetAttr(((PyObject *)((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->__pyx_base.topology), __pyx_n_normalize); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 227; goto __pyx_L1;}
  __pyx_3 = PyTuple_New(1); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 227; goto __pyx_L1;}
  Py_INCREF(__pyx_v_address);
  PyTuple_SET_ITEM(__pyx_3, 0, __pyx_v_address);
  __pyx_5 = PyObject_CallObject(__pyx_4, __pyx_3); if (!__pyx_5) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 227; goto __pyx_L1;}
  Py_DECREF(__pyx_4); __pyx_4 = 0;
  Py_DECREF(__pyx_3); __pyx_3 = 0;
  Py_DECREF(__pyx_v_address);
  __pyx_v_address = __pyx_5;
  __pyx_5 = 0;

  /* "/home/panx/ouroborus/birdcage/agent.pyx":228 */
  __pyx_4 = __Pyx_GetItemInt(__pyx_v_address, 0); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 228; goto __pyx_L1;}
  __pyx_2 = PyInt_AsLong(__pyx_4); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 228; goto __pyx_L1;}
  Py_DECREF(__pyx_4); __pyx_4 = 0;
  __pyx_3 = __Pyx_GetItemInt(__pyx_v_address, 1); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 228; goto __pyx_L1;}
  __pyx_6 = PyInt_AsLong(__pyx_3); if (PyErr_Occurred()) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 228; goto __pyx_L1;}
  Py_DECREF(__pyx_3); __pyx_3 = 0;
  ((struct __pyx_vtabstruct_5agent_Agent_2D *)((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->__pyx_base.__pyx_vtab)->pyx_move(((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self),__pyx_2,__pyx_6);

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_3);
  Py_XDECREF(__pyx_4);
  Py_XDECREF(__pyx_5);
  __Pyx_AddTraceback("agent.Agent_2D.move");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF((PyObject *)__pyx_v_self);
  Py_DECREF(__pyx_v_address);
  return __pyx_r;
}

static void __pyx_f_5agent_8Agent_2D_pyx_move(struct __pyx_obj_5agent_Agent_2D *__pyx_v_self,int __pyx_v_y1,int __pyx_v_y2) {
  Py_INCREF((PyObject *)__pyx_v_self);

  /* "/home/panx/ouroborus/birdcage/agent.pyx":237 */
  __pyx_v_self->x1 = ((struct __pyx_vtabstruct_8topology_GridTopology *)__pyx_v_self->__pyx_base.topology->__pyx_base.__pyx_vtab)->normal_x1(__pyx_v_self->__pyx_base.topology,__pyx_v_y1);

  /* "/home/panx/ouroborus/birdcage/agent.pyx":238 */
  __pyx_v_self->x2 = ((struct __pyx_vtabstruct_8topology_GridTopology *)__pyx_v_self->__pyx_base.topology->__pyx_base.__pyx_vtab)->normal_x2(__pyx_v_self->__pyx_base.topology,__pyx_v_y2);

  Py_DECREF((PyObject *)__pyx_v_self);
}

static PyObject *__pyx_f_5agent_8Agent_2D_tellDirections(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_5agent_8Agent_2D_tellDirections[] = "Return all the cells in the agent\'s sensoriality\n\n          return -->> a Python list of addresses";
static PyObject *__pyx_f_5agent_8Agent_2D_tellDirections(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  int __pyx_v_i;
  PyObject *__pyx_v_directions;
  PyObject *__pyx_r;
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  long __pyx_4;
  PyObject *__pyx_5 = 0;
  PyObject *__pyx_6 = 0;
  static char *__pyx_argnames[] = {0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "", __pyx_argnames)) return 0;
  Py_INCREF((PyObject *)__pyx_v_self);
  __pyx_v_directions = Py_None; Py_INCREF(Py_None);

  /* "/home/panx/ouroborus/birdcage/agent.pyx":249 */
  __pyx_1 = PyInt_FromLong(((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->x1); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 249; goto __pyx_L1;}
  __pyx_2 = PyInt_FromLong(((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->x2); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 249; goto __pyx_L1;}
  __pyx_3 = PyTuple_New(2); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 249; goto __pyx_L1;}
  PyTuple_SET_ITEM(__pyx_3, 0, __pyx_1);
  PyTuple_SET_ITEM(__pyx_3, 1, __pyx_2);
  __pyx_1 = 0;
  __pyx_2 = 0;
  __pyx_1 = PyList_New(1); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 249; goto __pyx_L1;}
  PyList_SET_ITEM(__pyx_1, 0, __pyx_3);
  __pyx_3 = 0;
  Py_DECREF(__pyx_v_directions);
  __pyx_v_directions = __pyx_1;
  __pyx_1 = 0;

  /* "/home/panx/ouroborus/birdcage/agent.pyx":250 */
  __pyx_4 = (((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->directions - 1);
  for (__pyx_v_i = 0; __pyx_v_i < __pyx_4; ++__pyx_v_i) {
    __pyx_2 = PyObject_GetAttr(__pyx_v_directions, __pyx_n_append); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 251; goto __pyx_L1;}
    __pyx_3 = PyObject_GetAttr(((PyObject *)((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->__pyx_base.sensoriality), __pyx_n_listNeighbors); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 251; goto __pyx_L1;}
    __pyx_1 = PyInt_FromLong(((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->x1); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 251; goto __pyx_L1;}
    __pyx_5 = PyInt_FromLong(((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->x2); if (!__pyx_5) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 251; goto __pyx_L1;}
    __pyx_6 = PyTuple_New(2); if (!__pyx_6) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 251; goto __pyx_L1;}
    PyTuple_SET_ITEM(__pyx_6, 0, __pyx_1);
    PyTuple_SET_ITEM(__pyx_6, 1, __pyx_5);
    __pyx_1 = 0;
    __pyx_5 = 0;
    __pyx_1 = PyTuple_New(1); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 251; goto __pyx_L1;}
    PyTuple_SET_ITEM(__pyx_1, 0, __pyx_6);
    __pyx_6 = 0;
    __pyx_5 = PyObject_CallObject(__pyx_3, __pyx_1); if (!__pyx_5) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 251; goto __pyx_L1;}
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    Py_DECREF(__pyx_1); __pyx_1 = 0;
    __pyx_6 = __Pyx_GetItemInt(__pyx_5, __pyx_v_i); if (!__pyx_6) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 251; goto __pyx_L1;}
    Py_DECREF(__pyx_5); __pyx_5 = 0;
    __pyx_3 = PyTuple_New(1); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 251; goto __pyx_L1;}
    PyTuple_SET_ITEM(__pyx_3, 0, __pyx_6);
    __pyx_6 = 0;
    __pyx_1 = PyObject_CallObject(__pyx_2, __pyx_3); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 251; goto __pyx_L1;}
    Py_DECREF(__pyx_2); __pyx_2 = 0;
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    Py_DECREF(__pyx_1); __pyx_1 = 0;
  }

  /* "/home/panx/ouroborus/birdcage/agent.pyx":252 */
  Py_INCREF(__pyx_v_directions);
  __pyx_r = __pyx_v_directions;
  goto __pyx_L0;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  Py_XDECREF(__pyx_5);
  Py_XDECREF(__pyx_6);
  __Pyx_AddTraceback("agent.Agent_2D.tellDirections");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_directions);
  Py_DECREF((PyObject *)__pyx_v_self);
  return __pyx_r;
}

static PyObject *__pyx_n_tellDirections;

static PyObject *__pyx_f_5agent_8Agent_2D_tellFacing(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_5agent_8Agent_2D_tellFacing[] = "Return the cell which the agent is facing\n\n          return -->> a Python 2-tuple";
static PyObject *__pyx_f_5agent_8Agent_2D_tellFacing(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_v_facing;
  PyObject *__pyx_r;
  PyObject *__pyx_1 = 0;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  static char *__pyx_argnames[] = {0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "", __pyx_argnames)) return 0;
  Py_INCREF((PyObject *)__pyx_v_self);
  __pyx_v_facing = Py_None; Py_INCREF(Py_None);

  /* "/home/panx/ouroborus/birdcage/agent.pyx":262 */
  __pyx_1 = PyObject_GetAttr(__pyx_v_self, __pyx_n_tellDirections); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 262; goto __pyx_L1;}
  __pyx_2 = PyObject_CallObject(__pyx_1, 0); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 262; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  __pyx_1 = __Pyx_GetItemInt(__pyx_2, ((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->facing); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 262; goto __pyx_L1;}
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  Py_DECREF(__pyx_v_facing);
  __pyx_v_facing = __pyx_1;
  __pyx_1 = 0;

  /* "/home/panx/ouroborus/birdcage/agent.pyx":263 */
  __pyx_2 = PyObject_GetAttr(((PyObject *)((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->__pyx_base.topology), __pyx_n_normalize); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 263; goto __pyx_L1;}
  __pyx_1 = PyTuple_New(1); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 263; goto __pyx_L1;}
  Py_INCREF(__pyx_v_facing);
  PyTuple_SET_ITEM(__pyx_1, 0, __pyx_v_facing);
  __pyx_3 = PyObject_CallObject(__pyx_2, __pyx_1); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 263; goto __pyx_L1;}
  Py_DECREF(__pyx_2); __pyx_2 = 0;
  Py_DECREF(__pyx_1); __pyx_1 = 0;
  __pyx_r = __pyx_3;
  __pyx_3 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  __Pyx_AddTraceback("agent.Agent_2D.tellFacing");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF(__pyx_v_facing);
  Py_DECREF((PyObject *)__pyx_v_self);
  return __pyx_r;
}

static PyObject *__pyx_n_NotInNeighborhoodError;

static PyObject *__pyx_f_5agent_8Agent_2D_changeFacing(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_5agent_8Agent_2D_changeFacing[] = "Change the direction in which the agent faces\n\n          facing ---> an integer\n          return -->> 1 if successful";
static PyObject *__pyx_f_5agent_8Agent_2D_changeFacing(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  int __pyx_v_facing;
  PyObject *__pyx_r;
  int __pyx_1;
  PyObject *__pyx_2 = 0;
  PyObject *__pyx_3 = 0;
  PyObject *__pyx_4 = 0;
  static char *__pyx_argnames[] = {"facing",0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "i", __pyx_argnames, &__pyx_v_facing)) return 0;
  Py_INCREF((PyObject *)__pyx_v_self);

  /* "/home/panx/ouroborus/birdcage/agent.pyx":272 */
  __pyx_1 = (((struct __pyx_vtabstruct_5agent_Agent_2D *)((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->__pyx_base.__pyx_vtab)->pyx_changeFacing(((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self),__pyx_v_facing) == (-1));
  if (__pyx_1) {
    __pyx_2 = __Pyx_GetName(__pyx_m, __pyx_n_E); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 273; goto __pyx_L1;}
    __pyx_3 = PyObject_GetAttr(__pyx_2, __pyx_n_NotInNeighborhoodError); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 273; goto __pyx_L1;}
    Py_DECREF(__pyx_2); __pyx_2 = 0;
    __pyx_2 = PyInt_FromLong(__pyx_v_facing); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 273; goto __pyx_L1;}
    __pyx_4 = PyTuple_New(2); if (!__pyx_4) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 273; goto __pyx_L1;}
    PyTuple_SET_ITEM(__pyx_4, 0, __pyx_2);
    Py_INCREF(((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->__pyx_base.sensoriality->name);
    PyTuple_SET_ITEM(__pyx_4, 1, ((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->__pyx_base.sensoriality->name);
    __pyx_2 = 0;
    __pyx_2 = PyObject_CallObject(__pyx_3, __pyx_4); if (!__pyx_2) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 273; goto __pyx_L1;}
    Py_DECREF(__pyx_3); __pyx_3 = 0;
    Py_DECREF(__pyx_4); __pyx_4 = 0;
    __Pyx_Raise(__pyx_2, 0, 0);
    Py_DECREF(__pyx_2); __pyx_2 = 0;
    {__pyx_filename = __pyx_f[0]; __pyx_lineno = 273; goto __pyx_L1;}
    goto __pyx_L2;
  }
  __pyx_L2:;

  /* "/home/panx/ouroborus/birdcage/agent.pyx":274 */
  __pyx_3 = PyInt_FromLong(1); if (!__pyx_3) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 274; goto __pyx_L1;}
  __pyx_r = __pyx_3;
  __pyx_3 = 0;
  goto __pyx_L0;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1:;
  Py_XDECREF(__pyx_2);
  Py_XDECREF(__pyx_3);
  Py_XDECREF(__pyx_4);
  __Pyx_AddTraceback("agent.Agent_2D.changeFacing");
  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF((PyObject *)__pyx_v_self);
  return __pyx_r;
}

static int __pyx_f_5agent_8Agent_2D_pyx_changeFacing(struct __pyx_obj_5agent_Agent_2D *__pyx_v_self,int __pyx_v_facing) {
  int __pyx_r;
  int __pyx_1;
  Py_INCREF((PyObject *)__pyx_v_self);
  __pyx_1 = (__pyx_v_facing < 0);
  if (!__pyx_1) {
    __pyx_1 = (__pyx_v_facing >= __pyx_v_self->directions);
  }
  if (__pyx_1) {
    __pyx_r = (-1);
    goto __pyx_L0;
    goto __pyx_L2;
  }
  /*else*/ {
    __pyx_v_self->facing = __pyx_v_facing;
  }
  __pyx_L2:;

  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF((PyObject *)__pyx_v_self);
  return __pyx_r;
}

static PyObject *__pyx_f_5agent_8Agent_2D_advance(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_5agent_8Agent_2D_advance[] = "Move the agent in the direction it\'s facing\n\n          return -->> True if the agent moved, False otherwise";
static PyObject *__pyx_f_5agent_8Agent_2D_advance(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_r;
  int __pyx_1;
  static char *__pyx_argnames[] = {0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "", __pyx_argnames)) return 0;
  Py_INCREF((PyObject *)__pyx_v_self);
  __pyx_1 = (((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->facing == 0);
  if (__pyx_1) {
    Py_INCREF(Py_False);
    __pyx_r = Py_False;
    goto __pyx_L0;
    goto __pyx_L2;
  }
  /*else*/ {

    /* "/home/panx/ouroborus/birdcage/agent.pyx":297 */
    ((struct __pyx_vtabstruct_5agent_Agent_2D *)((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->__pyx_base.__pyx_vtab)->pyx_advance(((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self));

    /* "/home/panx/ouroborus/birdcage/agent.pyx":298 */
    Py_INCREF(Py_True);
    __pyx_r = Py_True;
    goto __pyx_L0;
  }
  __pyx_L2:;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  __pyx_L0:;
  Py_DECREF((PyObject *)__pyx_v_self);
  return __pyx_r;
}

static int __pyx_f_5agent_8Agent_2D_pyx_advance(struct __pyx_obj_5agent_Agent_2D *__pyx_v_self) {
  int __pyx_v_y1;
  int __pyx_v_y2;
  int __pyx_r;
  int __pyx_1;
  Py_INCREF((PyObject *)__pyx_v_self);

  /* "/home/panx/ouroborus/birdcage/agent.pyx":306 */
  __pyx_1 = (__pyx_v_self->facing == 0);
  if (__pyx_1) {
    __pyx_r = 0;
    goto __pyx_L0;
    goto __pyx_L2;
  }
  /*else*/ {

    /* "/home/panx/ouroborus/birdcage/agent.pyx":309 */
    ((struct __pyx_vtabstruct_12neighborhood_Neighborhood_2D *)__pyx_v_self->__pyx_base.sensoriality->__pyx_vtab)->pyx_calculateNeighbors(__pyx_v_self->__pyx_base.sensoriality,__pyx_v_self->x1,__pyx_v_self->x2);

    /* "/home/panx/ouroborus/birdcage/agent.pyx":310 */
    __pyx_v_y1 = (__pyx_v_self->__pyx_base.sensoriality->neighbors_x1[(__pyx_v_self->facing - 1)]);

    /* "/home/panx/ouroborus/birdcage/agent.pyx":311 */
    __pyx_v_y2 = (__pyx_v_self->__pyx_base.sensoriality->neighbors_x2[(__pyx_v_self->facing - 1)]);

    /* "/home/panx/ouroborus/birdcage/agent.pyx":312 */
    ((struct __pyx_vtabstruct_5agent_Agent_2D *)__pyx_v_self->__pyx_base.__pyx_vtab)->pyx_move(__pyx_v_self,__pyx_v_y1,__pyx_v_y2);

    /* "/home/panx/ouroborus/birdcage/agent.pyx":313 */
    __pyx_r = 1;
    goto __pyx_L0;
  }
  __pyx_L2:;

  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF((PyObject *)__pyx_v_self);
  return __pyx_r;
}

static PyObject *__pyx_f_5agent_8Agent_2D_eatMana(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds); /*proto*/
static char __pyx_doc_5agent_8Agent_2D_eatMana[] = "Eat prana from the underlying cell\n\n          return -->> True if successful, False otherwise";
static PyObject *__pyx_f_5agent_8Agent_2D_eatMana(PyObject *__pyx_v_self, PyObject *__pyx_args, PyObject *__pyx_kwds) {
  PyObject *__pyx_r;
  int __pyx_1;
  static char *__pyx_argnames[] = {0};
  if (!PyArg_ParseTupleAndKeywords(__pyx_args, __pyx_kwds, "", __pyx_argnames)) return 0;
  Py_INCREF((PyObject *)__pyx_v_self);
  __pyx_1 = (((struct __pyx_vtabstruct_5agent_Agent_2D *)((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)->__pyx_base.__pyx_vtab)->pyx_eatMana(((struct __pyx_obj_5agent_Agent_2D *)__pyx_v_self)) == 0);
  if (__pyx_1) {
    Py_INCREF(Py_False);
    __pyx_r = Py_False;
    goto __pyx_L0;
    goto __pyx_L2;
  }
  /*else*/ {
    Py_INCREF(Py_True);
    __pyx_r = Py_True;
    goto __pyx_L0;
  }
  __pyx_L2:;

  __pyx_r = Py_None; Py_INCREF(Py_None);
  __pyx_L0:;
  Py_DECREF((PyObject *)__pyx_v_self);
  return __pyx_r;
}

static int __pyx_f_5agent_8Agent_2D_pyx_eatMana(struct __pyx_obj_5agent_Agent_2D *__pyx_v_self) {
  int __pyx_r;
  int __pyx_1;
  Py_INCREF((PyObject *)__pyx_v_self);
  __pyx_1 = (((struct __pyx_vtabstruct_8topology_GridTopology *)__pyx_v_self->__pyx_base.topology->__pyx_base.__pyx_vtab)->pyx_get(__pyx_v_self->__pyx_base.topology,__pyx_v_self->x1,__pyx_v_self->x2) == __pyx_v_self->__pyx_base.mana);
  if (__pyx_1) {

    /* "/home/panx/ouroborus/birdcage/agent.pyx":333 */
    ((struct __pyx_vtabstruct_5agent_Agent_2D *)__pyx_v_self->__pyx_base.__pyx_vtab)->__pyx_base.pyx_gainPrana(((struct __pyx_obj_5agent_Agent *)__pyx_v_self),5);

    /* "/home/panx/ouroborus/birdcage/agent.pyx":334 */
    ((struct __pyx_vtabstruct_8topology_GridTopology *)__pyx_v_self->__pyx_base.topology->__pyx_base.__pyx_vtab)->pyx_set(__pyx_v_self->__pyx_base.topology,__pyx_v_self->x1,__pyx_v_self->x2,__pyx_v_self->__pyx_base.topology->__pyx_base.background);

    /* "/home/panx/ouroborus/birdcage/agent.pyx":335 */
    __pyx_r = 1;
    goto __pyx_L0;
    goto __pyx_L2;
  }
  /*else*/ {
    __pyx_r = 0;
    goto __pyx_L0;
  }
  __pyx_L2:;

  __pyx_r = 0;
  __pyx_L0:;
  Py_DECREF((PyObject *)__pyx_v_self);
  return __pyx_r;
}

static __Pyx_InternTabEntry __pyx_intern_tab[] = {
  {&__pyx_n_ConflictingTopologyError, "ConflictingTopologyError"},
  {&__pyx_n_E, "E"},
  {&__pyx_n_InvalidAddressError, "InvalidAddressError"},
  {&__pyx_n_NotInNeighborhoodError, "NotInNeighborhoodError"},
  {&__pyx_n___init__, "__init__"},
  {&__pyx_n_append, "append"},
  {&__pyx_n_exceptions_birdcage, "exceptions_birdcage"},
  {&__pyx_n_listNeighbors, "listNeighbors"},
  {&__pyx_n_normalize, "normalize"},
  {&__pyx_n_tellDirections, "tellDirections"},
  {0, 0}
};

static __Pyx_StringTabEntry __pyx_string_tab[] = {
  {&__pyx_k2p, __pyx_k2, sizeof(__pyx_k2)},
  {&__pyx_k3p, __pyx_k3, sizeof(__pyx_k3)},
  {0, 0, 0}
};
static struct __pyx_vtabstruct_5agent_Agent __pyx_vtable_5agent_Agent;

static PyObject *__pyx_tp_new_5agent_Agent(PyTypeObject *t, PyObject *a, PyObject *k) {
  struct __pyx_obj_5agent_Agent *p;
  PyObject *o = (*t->tp_alloc)(t, 0);
  if (!o) return 0;
  p = ((struct __pyx_obj_5agent_Agent *)o);
  *(struct __pyx_vtabstruct_5agent_Agent **)&p->__pyx_vtab = __pyx_vtabptr_5agent_Agent;
  p->corporality = ((struct __pyx_obj_12neighborhood_Neighborhood_2D *)Py_None); Py_INCREF(Py_None);
  p->sensoriality = ((struct __pyx_obj_12neighborhood_Neighborhood_2D *)Py_None); Py_INCREF(Py_None);
  p->topology = ((struct __pyx_obj_8topology_GridTopology *)Py_None); Py_INCREF(Py_None);
  p->code = Py_None; Py_INCREF(Py_None);
  p->name = Py_None; Py_INCREF(Py_None);
  p->moira = Py_None; Py_INCREF(Py_None);
  return o;
}

static void __pyx_tp_dealloc_5agent_Agent(PyObject *o) {
  struct __pyx_obj_5agent_Agent *p = (struct __pyx_obj_5agent_Agent *)o;
  Py_XDECREF(((PyObject *)p->corporality));
  Py_XDECREF(((PyObject *)p->sensoriality));
  Py_XDECREF(((PyObject *)p->topology));
  Py_XDECREF(p->code);
  Py_XDECREF(p->name);
  Py_XDECREF(p->moira);
  (*o->ob_type->tp_free)(o);
}

static int __pyx_tp_traverse_5agent_Agent(PyObject *o, visitproc v, void *a) {
  int e;
  struct __pyx_obj_5agent_Agent *p = (struct __pyx_obj_5agent_Agent *)o;
  if (p->corporality) {
    e = (*v)(((PyObject*)p->corporality), a); if (e) return e;
  }
  if (p->sensoriality) {
    e = (*v)(((PyObject*)p->sensoriality), a); if (e) return e;
  }
  if (p->topology) {
    e = (*v)(((PyObject*)p->topology), a); if (e) return e;
  }
  if (p->code) {
    e = (*v)(p->code, a); if (e) return e;
  }
  if (p->name) {
    e = (*v)(p->name, a); if (e) return e;
  }
  if (p->moira) {
    e = (*v)(p->moira, a); if (e) return e;
  }
  return 0;
}

static int __pyx_tp_clear_5agent_Agent(PyObject *o) {
  struct __pyx_obj_5agent_Agent *p = (struct __pyx_obj_5agent_Agent *)o;
  PyObject *t;
  t = ((PyObject *)p->corporality); 
  p->corporality = ((struct __pyx_obj_12neighborhood_Neighborhood_2D *)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(t);
  t = ((PyObject *)p->sensoriality); 
  p->sensoriality = ((struct __pyx_obj_12neighborhood_Neighborhood_2D *)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(t);
  t = ((PyObject *)p->topology); 
  p->topology = ((struct __pyx_obj_8topology_GridTopology *)Py_None); Py_INCREF(Py_None);
  Py_XDECREF(t);
  t = p->code; 
  p->code = Py_None; Py_INCREF(Py_None);
  Py_XDECREF(t);
  t = p->name; 
  p->name = Py_None; Py_INCREF(Py_None);
  Py_XDECREF(t);
  t = p->moira; 
  p->moira = Py_None; Py_INCREF(Py_None);
  Py_XDECREF(t);
  return 0;
}

static struct PyMethodDef __pyx_methods_5agent_Agent[] = {
  {"isAlive", (PyCFunction)__pyx_f_5agent_5Agent_isAlive, METH_VARARGS|METH_KEYWORDS, __pyx_doc_5agent_5Agent_isAlive},
  {"tellPrana", (PyCFunction)__pyx_f_5agent_5Agent_tellPrana, METH_VARARGS|METH_KEYWORDS, __pyx_doc_5agent_5Agent_tellPrana},
  {"gainPrana", (PyCFunction)__pyx_f_5agent_5Agent_gainPrana, METH_VARARGS|METH_KEYWORDS, __pyx_doc_5agent_5Agent_gainPrana},
  {"losePrana", (PyCFunction)__pyx_f_5agent_5Agent_losePrana, METH_VARARGS|METH_KEYWORDS, __pyx_doc_5agent_5Agent_losePrana},
  {"zeroPrana", (PyCFunction)__pyx_f_5agent_5Agent_zeroPrana, METH_VARARGS|METH_KEYWORDS, __pyx_doc_5agent_5Agent_zeroPrana},
  {"update", (PyCFunction)__pyx_f_5agent_5Agent_update, METH_VARARGS|METH_KEYWORDS, __pyx_doc_5agent_5Agent_update},
  {0, 0, 0, 0}
};

static PyNumberMethods __pyx_tp_as_number_Agent = {
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

static PySequenceMethods __pyx_tp_as_sequence_Agent = {
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

static PyMappingMethods __pyx_tp_as_mapping_Agent = {
  0, /*mp_length*/
  0, /*mp_subscript*/
  0, /*mp_ass_subscript*/
};

static PyBufferProcs __pyx_tp_as_buffer_Agent = {
  0, /*bf_getreadbuffer*/
  0, /*bf_getwritebuffer*/
  0, /*bf_getsegcount*/
  0, /*bf_getcharbuffer*/
};

PyTypeObject __pyx_type_5agent_Agent = {
  PyObject_HEAD_INIT(0)
  0, /*ob_size*/
  "agent.Agent", /*tp_name*/
  sizeof(struct __pyx_obj_5agent_Agent), /*tp_basicsize*/
  0, /*tp_itemsize*/
  __pyx_tp_dealloc_5agent_Agent, /*tp_dealloc*/
  0, /*tp_print*/
  0, /*tp_getattr*/
  0, /*tp_setattr*/
  0, /*tp_compare*/
  0, /*tp_repr*/
  &__pyx_tp_as_number_Agent, /*tp_as_number*/
  &__pyx_tp_as_sequence_Agent, /*tp_as_sequence*/
  &__pyx_tp_as_mapping_Agent, /*tp_as_mapping*/
  0, /*tp_hash*/
  0, /*tp_call*/
  0, /*tp_str*/
  0, /*tp_getattro*/
  0, /*tp_setattro*/
  &__pyx_tp_as_buffer_Agent, /*tp_as_buffer*/
  Py_TPFLAGS_DEFAULT|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_HAVE_GC, /*tp_flags*/
  "Abstract base class for all agents", /*tp_doc*/
  __pyx_tp_traverse_5agent_Agent, /*tp_traverse*/
  __pyx_tp_clear_5agent_Agent, /*tp_clear*/
  0, /*tp_richcompare*/
  0, /*tp_weaklistoffset*/
  0, /*tp_iter*/
  0, /*tp_iternext*/
  __pyx_methods_5agent_Agent, /*tp_methods*/
  0, /*tp_members*/
  0, /*tp_getset*/
  0, /*tp_base*/
  0, /*tp_dict*/
  0, /*tp_descr_get*/
  0, /*tp_descr_set*/
  0, /*tp_dictoffset*/
  __pyx_f_5agent_5Agent___init__, /*tp_init*/
  0, /*tp_alloc*/
  __pyx_tp_new_5agent_Agent, /*tp_new*/
  0, /*tp_free*/
  0, /*tp_is_gc*/
  0, /*tp_bases*/
  0, /*tp_mro*/
  0, /*tp_cache*/
  0, /*tp_subclasses*/
  0, /*tp_weaklist*/
};
static struct __pyx_vtabstruct_5agent_Agent_2D __pyx_vtable_5agent_Agent_2D;

static PyObject *__pyx_tp_new_5agent_Agent_2D(PyTypeObject *t, PyObject *a, PyObject *k) {
  struct __pyx_obj_5agent_Agent_2D *p;
  PyObject *o = __pyx_ptype_5agent_Agent->tp_new(t, a, k);
  if (!o) return 0;
  p = ((struct __pyx_obj_5agent_Agent_2D *)o);
  *(struct __pyx_vtabstruct_5agent_Agent_2D **)&p->__pyx_base.__pyx_vtab = __pyx_vtabptr_5agent_Agent_2D;
  return o;
}

static void __pyx_tp_dealloc_5agent_Agent_2D(PyObject *o) {
  __pyx_ptype_5agent_Agent->tp_dealloc(o);
}

static struct PyMethodDef __pyx_methods_5agent_Agent_2D[] = {
  {"tellAddress", (PyCFunction)__pyx_f_5agent_8Agent_2D_tellAddress, METH_VARARGS|METH_KEYWORDS, __pyx_doc_5agent_8Agent_2D_tellAddress},
  {"tellCorporality", (PyCFunction)__pyx_f_5agent_8Agent_2D_tellCorporality, METH_VARARGS|METH_KEYWORDS, __pyx_doc_5agent_8Agent_2D_tellCorporality},
  {"move", (PyCFunction)__pyx_f_5agent_8Agent_2D_move, METH_VARARGS|METH_KEYWORDS, __pyx_doc_5agent_8Agent_2D_move},
  {"tellDirections", (PyCFunction)__pyx_f_5agent_8Agent_2D_tellDirections, METH_VARARGS|METH_KEYWORDS, __pyx_doc_5agent_8Agent_2D_tellDirections},
  {"tellFacing", (PyCFunction)__pyx_f_5agent_8Agent_2D_tellFacing, METH_VARARGS|METH_KEYWORDS, __pyx_doc_5agent_8Agent_2D_tellFacing},
  {"changeFacing", (PyCFunction)__pyx_f_5agent_8Agent_2D_changeFacing, METH_VARARGS|METH_KEYWORDS, __pyx_doc_5agent_8Agent_2D_changeFacing},
  {"advance", (PyCFunction)__pyx_f_5agent_8Agent_2D_advance, METH_VARARGS|METH_KEYWORDS, __pyx_doc_5agent_8Agent_2D_advance},
  {"eatMana", (PyCFunction)__pyx_f_5agent_8Agent_2D_eatMana, METH_VARARGS|METH_KEYWORDS, __pyx_doc_5agent_8Agent_2D_eatMana},
  {0, 0, 0, 0}
};

static PyNumberMethods __pyx_tp_as_number_Agent_2D = {
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

static PySequenceMethods __pyx_tp_as_sequence_Agent_2D = {
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

static PyMappingMethods __pyx_tp_as_mapping_Agent_2D = {
  0, /*mp_length*/
  0, /*mp_subscript*/
  0, /*mp_ass_subscript*/
};

static PyBufferProcs __pyx_tp_as_buffer_Agent_2D = {
  0, /*bf_getreadbuffer*/
  0, /*bf_getwritebuffer*/
  0, /*bf_getsegcount*/
  0, /*bf_getcharbuffer*/
};

PyTypeObject __pyx_type_5agent_Agent_2D = {
  PyObject_HEAD_INIT(0)
  0, /*ob_size*/
  "agent.Agent_2D", /*tp_name*/
  sizeof(struct __pyx_obj_5agent_Agent_2D), /*tp_basicsize*/
  0, /*tp_itemsize*/
  __pyx_tp_dealloc_5agent_Agent_2D, /*tp_dealloc*/
  0, /*tp_print*/
  0, /*tp_getattr*/
  0, /*tp_setattr*/
  0, /*tp_compare*/
  0, /*tp_repr*/
  &__pyx_tp_as_number_Agent_2D, /*tp_as_number*/
  &__pyx_tp_as_sequence_Agent_2D, /*tp_as_sequence*/
  &__pyx_tp_as_mapping_Agent_2D, /*tp_as_mapping*/
  0, /*tp_hash*/
  0, /*tp_call*/
  0, /*tp_str*/
  0, /*tp_getattro*/
  0, /*tp_setattro*/
  &__pyx_tp_as_buffer_Agent_2D, /*tp_as_buffer*/
  Py_TPFLAGS_DEFAULT|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_BASETYPE, /*tp_flags*/
  "Base class for all agents based on a two-dimensional automaton.", /*tp_doc*/
  0, /*tp_traverse*/
  0, /*tp_clear*/
  0, /*tp_richcompare*/
  0, /*tp_weaklistoffset*/
  0, /*tp_iter*/
  0, /*tp_iternext*/
  __pyx_methods_5agent_Agent_2D, /*tp_methods*/
  0, /*tp_members*/
  0, /*tp_getset*/
  0, /*tp_base*/
  0, /*tp_dict*/
  0, /*tp_descr_get*/
  0, /*tp_descr_set*/
  0, /*tp_dictoffset*/
  __pyx_f_5agent_8Agent_2D___init__, /*tp_init*/
  0, /*tp_alloc*/
  __pyx_tp_new_5agent_Agent_2D, /*tp_new*/
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

PyMODINIT_FUNC initagent(void); /*proto*/
PyMODINIT_FUNC initagent(void) {
  PyObject *__pyx_1 = 0;
  __pyx_init_filenames();
  __pyx_m = Py_InitModule4("agent", __pyx_methods, 0, 0, PYTHON_API_VERSION);
  if (!__pyx_m) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 23; goto __pyx_L1;};
  Py_INCREF(__pyx_m);
  __pyx_b = PyImport_AddModule("__builtin__");
  if (!__pyx_b) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 23; goto __pyx_L1;};
  if (PyObject_SetAttrString(__pyx_m, "__builtins__", __pyx_b) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 23; goto __pyx_L1;};
  if (__Pyx_InternStrings(__pyx_intern_tab) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 23; goto __pyx_L1;};
  if (__Pyx_InitStrings(__pyx_string_tab) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 23; goto __pyx_L1;};
  __pyx_vtabptr_5agent_Agent = &__pyx_vtable_5agent_Agent;
  *(void(**)(void))&__pyx_vtable_5agent_Agent.pyx_isAlive = (void(*)(void))__pyx_f_5agent_5Agent_pyx_isAlive;
  *(void(**)(void))&__pyx_vtable_5agent_Agent.pyx_tellPrana = (void(*)(void))__pyx_f_5agent_5Agent_pyx_tellPrana;
  *(void(**)(void))&__pyx_vtable_5agent_Agent.pyx_gainPrana = (void(*)(void))__pyx_f_5agent_5Agent_pyx_gainPrana;
  *(void(**)(void))&__pyx_vtable_5agent_Agent.pyx_losePrana = (void(*)(void))__pyx_f_5agent_5Agent_pyx_losePrana;
  *(void(**)(void))&__pyx_vtable_5agent_Agent.pyx_zeroPrana = (void(*)(void))__pyx_f_5agent_5Agent_pyx_zeroPrana;
  *(void(**)(void))&__pyx_vtable_5agent_Agent.pyx_update = (void(*)(void))__pyx_f_5agent_5Agent_pyx_update;
  __pyx_type_5agent_Agent.tp_free = _PyObject_GC_Del;
  if (PyType_Ready(&__pyx_type_5agent_Agent) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 32; goto __pyx_L1;}
  if (__Pyx_SetVtable(__pyx_type_5agent_Agent.tp_dict, __pyx_vtabptr_5agent_Agent) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 32; goto __pyx_L1;}
  if (PyObject_SetAttrString(__pyx_m, "Agent", (PyObject *)&__pyx_type_5agent_Agent) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 32; goto __pyx_L1;}
  __pyx_ptype_5agent_Agent = &__pyx_type_5agent_Agent;
  __pyx_vtabptr_5agent_Agent_2D = &__pyx_vtable_5agent_Agent_2D;
  __pyx_vtable_5agent_Agent_2D.__pyx_base = *__pyx_vtabptr_5agent_Agent;
  *(void(**)(void))&__pyx_vtable_5agent_Agent_2D.pyx_move = (void(*)(void))__pyx_f_5agent_8Agent_2D_pyx_move;
  *(void(**)(void))&__pyx_vtable_5agent_Agent_2D.pyx_changeFacing = (void(*)(void))__pyx_f_5agent_8Agent_2D_pyx_changeFacing;
  *(void(**)(void))&__pyx_vtable_5agent_Agent_2D.pyx_advance = (void(*)(void))__pyx_f_5agent_8Agent_2D_pyx_advance;
  *(void(**)(void))&__pyx_vtable_5agent_Agent_2D.pyx_eatMana = (void(*)(void))__pyx_f_5agent_8Agent_2D_pyx_eatMana;
  __pyx_type_5agent_Agent_2D.tp_base = __pyx_ptype_5agent_Agent;
  if (PyType_Ready(&__pyx_type_5agent_Agent_2D) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 168; goto __pyx_L1;}
  if (__Pyx_SetVtable(__pyx_type_5agent_Agent_2D.tp_dict, __pyx_vtabptr_5agent_Agent_2D) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 168; goto __pyx_L1;}
  if (PyObject_SetAttrString(__pyx_m, "Agent_2D", (PyObject *)&__pyx_type_5agent_Agent_2D) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 168; goto __pyx_L1;}
  __pyx_ptype_5agent_Agent_2D = &__pyx_type_5agent_Agent_2D;
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
  __pyx_ptype_6genome_Genome = __Pyx_ImportType("genome", "Genome", sizeof(struct __pyx_obj_6genome_Genome)); if (!__pyx_ptype_6genome_Genome) {__pyx_filename = __pyx_f[3]; __pyx_lineno = 12; goto __pyx_L1;}
  if (__Pyx_GetVtable(__pyx_ptype_6genome_Genome->tp_dict, &__pyx_vtabptr_6genome_Genome) < 0) {__pyx_filename = __pyx_f[3]; __pyx_lineno = 12; goto __pyx_L1;}

  /* "/home/panx/ouroborus/birdcage/agent.pyx":23 */
  __pyx_1 = __Pyx_Import(__pyx_n_exceptions_birdcage, 0); if (!__pyx_1) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 23; goto __pyx_L1;}
  if (PyObject_SetAttr(__pyx_m, __pyx_n_E, __pyx_1) < 0) {__pyx_filename = __pyx_f[0]; __pyx_lineno = 23; goto __pyx_L1;}
  Py_DECREF(__pyx_1); __pyx_1 = 0;

  /* "/home/panx/ouroborus/birdcage/agent.pyx":327 */
  return;
  __pyx_L1:;
  Py_XDECREF(__pyx_1);
  __Pyx_AddTraceback("agent");
}

static char *__pyx_filenames[] = {
  "agent.pyx",
  "topology.pxd",
  "neighborhood.pxd",
  "genome.pxd",
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
