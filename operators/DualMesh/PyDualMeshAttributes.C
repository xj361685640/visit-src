/*****************************************************************************
*
* Copyright (c) 2000 - 2018, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* LLNL-CODE-442911
* All rights reserved.
*
* This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
* full copyright notice is contained in the file COPYRIGHT located at the root
* of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
*
* Redistribution  and  use  in  source  and  binary  forms,  with  or  without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of  source code must  retain the above  copyright notice,
*    this list of conditions and the disclaimer below.
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
*    documentation and/or other materials provided with the distribution.
*  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
* LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
* DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

#include <PyDualMeshAttributes.h>
#include <ObserverToCallback.h>
#include <stdio.h>
#include <snprintf.h>

// ****************************************************************************
// Module: PyDualMeshAttributes
//
// Purpose: 
//   Atts for Dual Mesh Operator
//
// Note:       Autogenerated by xml2python. Do not modify by hand!
//
// Programmer: xml2python
// Creation:   omitted
//
// ****************************************************************************

//
// This struct contains the Python type information and a DualMeshAttributes.
//
struct DualMeshAttributesObject
{
    PyObject_HEAD
    DualMeshAttributes *data;
    bool        owns;
    PyObject   *parent;
};

//
// Internal prototypes
//
static PyObject *NewDualMeshAttributes(int);

std::string
PyDualMeshAttributes_ToString(const DualMeshAttributes *atts, const char *prefix)
{
    std::string str;
    char tmpStr[1000];

    const char *mode_names = "Auto, NodesToZones, ZonesToNodes";
    switch (atts->GetMode())
    {
      case DualMeshAttributes::Auto:
          SNPRINTF(tmpStr, 1000, "%smode = %sAuto  # %s\n", prefix, prefix, mode_names);
          str += tmpStr;
          break;
      case DualMeshAttributes::NodesToZones:
          SNPRINTF(tmpStr, 1000, "%smode = %sNodesToZones  # %s\n", prefix, prefix, mode_names);
          str += tmpStr;
          break;
      case DualMeshAttributes::ZonesToNodes:
          SNPRINTF(tmpStr, 1000, "%smode = %sZonesToNodes  # %s\n", prefix, prefix, mode_names);
          str += tmpStr;
          break;
      default:
          break;
    }

    return str;
}

static PyObject *
DualMeshAttributes_Notify(PyObject *self, PyObject *args)
{
    DualMeshAttributesObject *obj = (DualMeshAttributesObject *)self;
    obj->data->Notify();
    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
DualMeshAttributes_SetMode(PyObject *self, PyObject *args)
{
    DualMeshAttributesObject *obj = (DualMeshAttributesObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the mode in the object.
    if(ival >= 0 && ival < 3)
        obj->data->SetMode(DualMeshAttributes::ConversionMode(ival));
    else
    {
        fprintf(stderr, "An invalid mode value was given. "
                        "Valid values are in the range of [0,2]. "
                        "You can also use the following names: "
                        "Auto, NodesToZones, ZonesToNodes.");
        return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
DualMeshAttributes_GetMode(PyObject *self, PyObject *args)
{
    DualMeshAttributesObject *obj = (DualMeshAttributesObject *)self;
    PyObject *retval = PyInt_FromLong(long(obj->data->GetMode()));
    return retval;
}



PyMethodDef PyDualMeshAttributes_methods[DUALMESHATTRIBUTES_NMETH] = {
    {"Notify", DualMeshAttributes_Notify, METH_VARARGS},
    {"SetMode", DualMeshAttributes_SetMode, METH_VARARGS},
    {"GetMode", DualMeshAttributes_GetMode, METH_VARARGS},
    {NULL, NULL}
};

//
// Type functions
//

static void
DualMeshAttributes_dealloc(PyObject *v)
{
   DualMeshAttributesObject *obj = (DualMeshAttributesObject *)v;
   if(obj->parent != 0)
       Py_DECREF(obj->parent);
   if(obj->owns)
       delete obj->data;
}

static int
DualMeshAttributes_compare(PyObject *v, PyObject *w)
{
    DualMeshAttributes *a = ((DualMeshAttributesObject *)v)->data;
    DualMeshAttributes *b = ((DualMeshAttributesObject *)w)->data;
    return (*a == *b) ? 0 : -1;
}

PyObject *
PyDualMeshAttributes_getattr(PyObject *self, char *name)
{
    if(strcmp(name, "mode") == 0)
        return DualMeshAttributes_GetMode(self, NULL);
    if(strcmp(name, "Auto") == 0)
        return PyInt_FromLong(long(DualMeshAttributes::Auto));
    if(strcmp(name, "NodesToZones") == 0)
        return PyInt_FromLong(long(DualMeshAttributes::NodesToZones));
    if(strcmp(name, "ZonesToNodes") == 0)
        return PyInt_FromLong(long(DualMeshAttributes::ZonesToNodes));


    return Py_FindMethod(PyDualMeshAttributes_methods, self, name);
}

int
PyDualMeshAttributes_setattr(PyObject *self, char *name, PyObject *args)
{
    // Create a tuple to contain the arguments since all of the Set
    // functions expect a tuple.
    PyObject *tuple = PyTuple_New(1);
    PyTuple_SET_ITEM(tuple, 0, args);
    Py_INCREF(args);
    PyObject *obj = NULL;

    if(strcmp(name, "mode") == 0)
        obj = DualMeshAttributes_SetMode(self, tuple);

    if(obj != NULL)
        Py_DECREF(obj);

    Py_DECREF(tuple);
    if( obj == NULL)
        PyErr_Format(PyExc_RuntimeError, "Unable to set unknown attribute: '%s'", name);
    return (obj != NULL) ? 0 : -1;
}

static int
DualMeshAttributes_print(PyObject *v, FILE *fp, int flags)
{
    DualMeshAttributesObject *obj = (DualMeshAttributesObject *)v;
    fprintf(fp, "%s", PyDualMeshAttributes_ToString(obj->data, "").c_str());
    return 0;
}

PyObject *
DualMeshAttributes_str(PyObject *v)
{
    DualMeshAttributesObject *obj = (DualMeshAttributesObject *)v;
    return PyString_FromString(PyDualMeshAttributes_ToString(obj->data,"").c_str());
}

//
// The doc string for the class.
//
#if PY_MAJOR_VERSION > 2 || (PY_MAJOR_VERSION == 2 && PY_MINOR_VERSION >= 5)
static const char *DualMeshAttributes_Purpose = "Atts for Dual Mesh Operator";
#else
static char *DualMeshAttributes_Purpose = "Atts for Dual Mesh Operator";
#endif

//
// The type description structure
//
static PyTypeObject DualMeshAttributesType =
{
    //
    // Type header
    //
    PyObject_HEAD_INIT(&PyType_Type)
    0,                                   // ob_size
    "DualMeshAttributes",                    // tp_name
    sizeof(DualMeshAttributesObject),        // tp_basicsize
    0,                                   // tp_itemsize
    //
    // Standard methods
    //
    (destructor)DualMeshAttributes_dealloc,  // tp_dealloc
    (printfunc)DualMeshAttributes_print,     // tp_print
    (getattrfunc)PyDualMeshAttributes_getattr, // tp_getattr
    (setattrfunc)PyDualMeshAttributes_setattr, // tp_setattr
    (cmpfunc)DualMeshAttributes_compare,     // tp_compare
    (reprfunc)0,                         // tp_repr
    //
    // Type categories
    //
    0,                                   // tp_as_number
    0,                                   // tp_as_sequence
    0,                                   // tp_as_mapping
    //
    // More methods
    //
    0,                                   // tp_hash
    0,                                   // tp_call
    (reprfunc)DualMeshAttributes_str,        // tp_str
    0,                                   // tp_getattro
    0,                                   // tp_setattro
    0,                                   // tp_as_buffer
    Py_TPFLAGS_CHECKTYPES,               // tp_flags
    DualMeshAttributes_Purpose,              // tp_doc
    0,                                   // tp_traverse
    0,                                   // tp_clear
    0,                                   // tp_richcompare
    0                                    // tp_weaklistoffset
};

//
// Helper functions for object allocation.
//

static DualMeshAttributes *defaultAtts = 0;
static DualMeshAttributes *currentAtts = 0;

static PyObject *
NewDualMeshAttributes(int useCurrent)
{
    DualMeshAttributesObject *newObject;
    newObject = PyObject_NEW(DualMeshAttributesObject, &DualMeshAttributesType);
    if(newObject == NULL)
        return NULL;
    if(useCurrent && currentAtts != 0)
        newObject->data = new DualMeshAttributes(*currentAtts);
    else if(defaultAtts != 0)
        newObject->data = new DualMeshAttributes(*defaultAtts);
    else
        newObject->data = new DualMeshAttributes;
    newObject->owns = true;
    newObject->parent = 0;
    return (PyObject *)newObject;
}

static PyObject *
WrapDualMeshAttributes(const DualMeshAttributes *attr)
{
    DualMeshAttributesObject *newObject;
    newObject = PyObject_NEW(DualMeshAttributesObject, &DualMeshAttributesType);
    if(newObject == NULL)
        return NULL;
    newObject->data = (DualMeshAttributes *)attr;
    newObject->owns = false;
    newObject->parent = 0;
    return (PyObject *)newObject;
}

///////////////////////////////////////////////////////////////////////////////
//
// Interface that is exposed to the VisIt module.
//
///////////////////////////////////////////////////////////////////////////////

PyObject *
DualMeshAttributes_new(PyObject *self, PyObject *args)
{
    int useCurrent = 0;
    if (!PyArg_ParseTuple(args, "i", &useCurrent))
    {
        if (!PyArg_ParseTuple(args, ""))
            return NULL;
        else
            PyErr_Clear();
    }

    return (PyObject *)NewDualMeshAttributes(useCurrent);
}

//
// Plugin method table. These methods are added to the visitmodule's methods.
//
static PyMethodDef DualMeshAttributesMethods[] = {
    {"DualMeshAttributes", DualMeshAttributes_new, METH_VARARGS},
    {NULL,      NULL}        /* Sentinel */
};

static Observer *DualMeshAttributesObserver = 0;

std::string
PyDualMeshAttributes_GetLogString()
{
    std::string s("DualMeshAtts = DualMeshAttributes()\n");
    if(currentAtts != 0)
        s += PyDualMeshAttributes_ToString(currentAtts, "DualMeshAtts.");
    return s;
}

static void
PyDualMeshAttributes_CallLogRoutine(Subject *subj, void *data)
{
    typedef void (*logCallback)(const std::string &);
    logCallback cb = (logCallback)data;

    if(cb != 0)
    {
        std::string s("DualMeshAtts = DualMeshAttributes()\n");
        s += PyDualMeshAttributes_ToString(currentAtts, "DualMeshAtts.");
        cb(s);
    }
}

void
PyDualMeshAttributes_StartUp(DualMeshAttributes *subj, void *data)
{
    if(subj == 0)
        return;

    currentAtts = subj;
    PyDualMeshAttributes_SetDefaults(subj);

    //
    // Create the observer that will be notified when the attributes change.
    //
    if(DualMeshAttributesObserver == 0)
    {
        DualMeshAttributesObserver = new ObserverToCallback(subj,
            PyDualMeshAttributes_CallLogRoutine, (void *)data);
    }

}

void
PyDualMeshAttributes_CloseDown()
{
    delete defaultAtts;
    defaultAtts = 0;
    delete DualMeshAttributesObserver;
    DualMeshAttributesObserver = 0;
}

PyMethodDef *
PyDualMeshAttributes_GetMethodTable(int *nMethods)
{
    *nMethods = 1;
    return DualMeshAttributesMethods;
}

bool
PyDualMeshAttributes_Check(PyObject *obj)
{
    return (obj->ob_type == &DualMeshAttributesType);
}

DualMeshAttributes *
PyDualMeshAttributes_FromPyObject(PyObject *obj)
{
    DualMeshAttributesObject *obj2 = (DualMeshAttributesObject *)obj;
    return obj2->data;
}

PyObject *
PyDualMeshAttributes_New()
{
    return NewDualMeshAttributes(0);
}

PyObject *
PyDualMeshAttributes_Wrap(const DualMeshAttributes *attr)
{
    return WrapDualMeshAttributes(attr);
}

void
PyDualMeshAttributes_SetParent(PyObject *obj, PyObject *parent)
{
    DualMeshAttributesObject *obj2 = (DualMeshAttributesObject *)obj;
    obj2->parent = parent;
}

void
PyDualMeshAttributes_SetDefaults(const DualMeshAttributes *atts)
{
    if(defaultAtts)
        delete defaultAtts;

    defaultAtts = new DualMeshAttributes(*atts);
}

