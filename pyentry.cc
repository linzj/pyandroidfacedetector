#include <Python.h>
#include <structmember.h>
#include <stdlib.h>
#include <stddef.h>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define FULL_MODULE_NAME "AndroidFaceDetector"

using std::string;

extern "C" {
#include <fd_emb_sdk.h>
void initpyandroidfacedetector(void);
}

class AutoPyObject {
 public:
  explicit AutoPyObject(PyObject*);
  ~AutoPyObject();
  AutoPyObject(AutoPyObject&) = delete;
  AutoPyObject& operator=(AutoPyObject&) = delete;
  AutoPyObject(AutoPyObject&&);
  AutoPyObject& operator=(AutoPyObject&&);
  operator PyObject*();
  typedef PyObject*(AutoPyObject::*UnspecifiedBoolType);
  operator UnspecifiedBoolType() const {
    return o_ ? &AutoPyObject::o_ : nullptr;
  }
  inline PyObject* release();
  inline PyObject* get();

 private:
  PyObject* o_;
};

AutoPyObject::AutoPyObject(PyObject* o) : o_(o) {}
AutoPyObject::~AutoPyObject() {
  if (o_) {
    Py_DECREF(o_);
  }
}

AutoPyObject::AutoPyObject(AutoPyObject&& rhs) {
  o_ = rhs.o_;
  rhs.o_ = nullptr;
}

AutoPyObject& AutoPyObject::operator=(AutoPyObject&& rhs) {
  o_ = rhs.o_;
  rhs.o_ = nullptr;
  return *this;
}

PyObject* AutoPyObject::release() {
  PyObject* o = o_;
  o_ = nullptr;
  return o;
}

PyObject* AutoPyObject::get() {
  PyObject* o = o_;
  return o;
}

template <typename T>
AutoPyObject makeAutoPyObject(T* o) {
  AutoPyObject ao((PyObject*)o);
  return ao;
}

AutoPyObject::operator PyObject*() {
  return o_;
}

static void doThrowNoMemory(const char* msg) {
  PyErr_SetString(PyExc_MemoryError, msg);
}

struct PyFaceData {
  PyObject_HEAD;

  float confidence;
  float midpointx;
  float midpointy;
  float eyedist;
};

static PyMemberDef PyFaceData_members[] = {
    {(char*)"confidence", T_FLOAT, offsetof(PyFaceData, confidence), 0,
     (char*)"confidence of correctness"},
    {(char*)"midpointx", T_FLOAT, offsetof(PyFaceData, midpointx), 0,
     (char*)"midpointx of a face"},
    {(char*)"midpointy", T_FLOAT, offsetof(PyFaceData, midpointy), 0,
     (char*)"midpointy of a face"},
    {(char*)"eyedist", T_FLOAT, offsetof(PyFaceData, eyedist), 0,
     (char*)"the distance of eyes"},
    {NULL} /* Sentinel */
};

static PyTypeObject PyFaceData_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0) FULL_MODULE_NAME
    ".FaceDetector",     // tp_name
    sizeof(PyFaceData),  // tp_basicsize
    0,                   // tp_itemsize
    0,                   // tp_dealloc
    0,                   // tp_print
    0,                   // tp_getattr
    0,                   // tp_setattr
    0,                   // tp_compare
    0,                   // tp_repr
    0,                   // tp_as_number
    0,                   // tp_as_sequence
    0,                   // tp_as_mapping
    0,                   // tp_hash
    0,                   // tp_call
    0,                   // tp_str
    0,                   // tp_getattro
    0,                   // tp_setattro
    0,                   // tp_as_buffer
    Py_TPFLAGS_DEFAULT,  // tp_flags
    "The Face Data",     // tp_doc
    0,                   // tp_traverse
    0,                   // tp_clear
    0,                   // tp_richcompare
    0,                   // tp_weaklistoffset
    0,                   // tp_iter
    0,                   // tp_iternext
    0,                   // tp_methods
    PyFaceData_members,  // tp_members
    0,                   // tp_getset
    0,                   // tp_base
    0,                   // tp_dict
    0,                   // tp_descr_get
    0,                   // tp_descr_set
    0,                   // tp_dictoffset
};

struct PyFaceDetector {
  PyObject_HEAD;

  btk_HSDK sdk;
  btk_HDCR dcr;
  btk_HFaceFinder fd;
  int width;
  int height;
  int maxFaces;
};

static int FaceDetectorInit(PyFaceDetector* self,
                            PyObject* args,
                            PyObject* kwds);

static void FaceDetectorDealloc(PyObject* self);
static PyObject* FaceDetectMethod(PyFaceDetector* self, PyObject* args);
static PyObject* FaceGetFaceMethod(PyFaceDetector* self, PyObject* args);

static PyMethodDef FaceDetectorMethods[] = {
    {
        "Detect", (PyCFunction)FaceDetectMethod, METH_VARARGS,
    },
    {
        "GetFace", (PyCFunction)FaceGetFaceMethod, METH_VARARGS,
    },
    {NULL}};

static PyTypeObject PyFaceDetector_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0) FULL_MODULE_NAME
    ".FaceDetector",             // tp_name
    sizeof(PyFaceDetector),      // tp_basicsize
    0,                           // tp_itemsize
    FaceDetectorDealloc,         // tp_dealloc
    0,                           // tp_print
    0,                           // tp_getattr
    0,                           // tp_setattr
    0,                           // tp_compare
    0,                           // tp_repr
    0,                           // tp_as_number
    0,                           // tp_as_sequence
    0,                           // tp_as_mapping
    0,                           // tp_hash
    0,                           // tp_call
    0,                           // tp_str
    0,                           // tp_getattro
    0,                           // tp_setattro
    0,                           // tp_as_buffer
    Py_TPFLAGS_DEFAULT,          // tp_flags
    "The Face Detector",         // tp_doc
    0,                           // tp_traverse
    0,                           // tp_clear
    0,                           // tp_richcompare
    0,                           // tp_weaklistoffset
    0,                           // tp_iter
    0,                           // tp_iternext
    FaceDetectorMethods,         // tp_methods
    0,                           // tp_members
    0,                           // tp_getset
    0,                           // tp_base
    0,                           // tp_dict
    0,                           // tp_descr_get
    0,                           // tp_descr_set
    0,                           // tp_dictoffset
    (initproc)FaceDetectorInit,  // tp_init
    0,                           // tp_alloc
    PyType_GenericNew,           // tp_new
    PyObject_Del,                // tp_free
};

static bool initialize(PyFaceDetector* self, const char* modulePath) {
  // load the configuration file
  string path(modulePath);
  path.append("/RFFstd_501.bmd");
  // path.appendPath("usr/share/bmd/RFFspeed_501.bmd");

  const int MAX_FILE_SIZE = 65536;
  void* initData = malloc(MAX_FILE_SIZE); /* enough to fit entire file */
  int filedesc = open(path.c_str(), O_RDONLY);
  if (filedesc == -1)
    return false;
  int initDataSize = read(filedesc, initData, MAX_FILE_SIZE);
  close(filedesc);

  // --------------------------------------------------------------------
  btk_HSDK sdk = nullptr;
  btk_SDKCreateParam sdkParam = btk_SDK_defaultParam();
  sdkParam.fpMalloc = malloc;
  sdkParam.fpFree = free;
  sdkParam.maxImageWidth = self->width;
  sdkParam.maxImageHeight = self->height;

  btk_Status status = btk_SDK_create(&sdkParam, &sdk);
  // make sure everything went well
  if (status != btk_STATUS_OK) {
    // XXX: be more precise about what went wrong
    doThrowNoMemory("btk_SDK_create failed");
    return false;
  }

  btk_HDCR dcr = NULL;
  btk_DCRCreateParam dcrParam = btk_DCR_defaultParam();
  btk_DCR_create(sdk, &dcrParam, &dcr);

  btk_HFaceFinder fd = NULL;
  btk_FaceFinderCreateParam fdParam = btk_FaceFinder_defaultParam();
  fdParam.pModuleParam = initData;
  fdParam.moduleParamSize = initDataSize;
  fdParam.maxDetectableFaces = self->maxFaces;
  status = btk_FaceFinder_create(sdk, &fdParam, &fd);
  btk_FaceFinder_setRange(fd, 20, self->width / 2); /* set eye distance range */

  // make sure everything went well
  if (status != btk_STATUS_OK) {
    // XXX: be more precise about what went wrong
    fprintf(stderr, "btk_FaceFinder_create failed: %d.\n", status);
    doThrowNoMemory("btk_FaceFinder_create failed");
    return false;
  }

  // free the configuration file
  free(initData);

  // initialize the java object
  self->fd = fd;
  self->sdk = sdk;
  self->dcr = dcr;
  return true;
}

static int FaceDetectorInit(PyFaceDetector* self,
                            PyObject* args,
                            PyObject* kwds) {
  static char* kwlist[] = {(char*)"path", (char*)"width", (char*)"height",
                           (char*)"maxFaces", NULL};
  const char* modulePath;

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "siii", kwlist, &modulePath,
                                   &self->width, &self->height,
                                   &self->maxFaces)) {
    PyErr_SetString(PyExc_KeyError, "init arguments has invalid keys");
    return -1;
  }
  if (!initialize(self, modulePath)) {
    return -1;
  }
  return 0;
}

static void FaceDetectorDealloc(PyObject* self) {
  PyFaceDetector* _self = reinterpret_cast<PyFaceDetector*>(self);
  btk_HFaceFinder hfd = _self->fd;
  btk_FaceFinder_close(hfd);

  btk_HDCR hdcr = _self->dcr;
  btk_DCR_close(hdcr);

  btk_HSDK hsdk = _self->sdk;
  btk_SDK_close(hsdk);
  Py_TYPE(self)->tp_free((PyObject*)self);
}

static void getFaceData(btk_HDCR hdcr, PyFaceData* fdata) {
  btk_Node leftEye, rightEye;

  btk_DCR_getNode(hdcr, 0, &leftEye);
  btk_DCR_getNode(hdcr, 1, &rightEye);

  fdata->eyedist = (float)(rightEye.x - leftEye.x) / (1 << 16);
  fdata->midpointx = (float)(rightEye.x + leftEye.x) / (1 << 17);
  fdata->midpointy = (float)(rightEye.y + leftEye.y) / (1 << 17);
  fdata->confidence = (float)btk_DCR_confidence(hdcr) / (1 << 24);
}

static PyObject* GetFace(PyFaceDetector* self, int f) {
  btk_HDCR hdcr = self->dcr;
  btk_HFaceFinder hfd = self->fd;

  PyFaceData* faceData;
  AutoPyObject scopedObject(PyObject_New(PyObject, &PyFaceData_Type));
  if (!scopedObject) {
    return nullptr;
  }
  faceData = reinterpret_cast<PyFaceData*>(scopedObject.get());
  btk_FaceFinder_getDCR(hfd, hdcr);
  getFaceData(hdcr, faceData);
  return scopedObject.release();
}

static PyObject* FaceGetFaceMethod(PyFaceDetector* self, PyObject* args) {
  int face;
  if (!PyArg_ParseTuple(args, "i", &face)) {
    PyErr_SetString(PyExc_TypeError, "argument 1 should be a integer");
    return nullptr;
  }
  return GetFace(self, face);
}

static PyObject* Detect(PyFaceDetector* self, PyObject* o) {
  // check parameters
  AutoPyObject byteArray(PyByteArray_FromObject(o));
  if (!byteArray) {
    PyErr_SetString(PyExc_TypeError,
                    "byteArray argument should be a byte array");
    return nullptr;
  }
  u32 width = self->width;
  u32 height = self->height;
  if (PyByteArray_Size(byteArray.get()) != width * height) {
    PyErr_Format(
        PyExc_KeyError,
        "The size of byteArray does not equal to width * height = %d, but %d",
        width * height, PyByteArray_Size(byteArray.get()));
    return nullptr;
  }
  // get the fields we need
  btk_HDCR hdcr = self->dcr;
  btk_HFaceFinder hfd = self->fd;

  // run detection
  btk_DCR_assignGrayByteImage(hdcr, PyByteArray_AsString(byteArray.get()),
                              width, height);

  int numberOfFaces = 0;
  if (btk_FaceFinder_putDCR(hfd, hdcr) == btk_STATUS_OK) {
    numberOfFaces = btk_FaceFinder_faces(hfd);
  } else {
    PyErr_SetString(
        PyExc_RuntimeError,
        "ERROR: Return 0 faces because error exists in btk_FaceFinder_putDCR.");
    return nullptr;
  }
  return PyInt_FromSsize_t(numberOfFaces);
}

static PyObject* FaceDetectMethod(PyFaceDetector* self, PyObject* args) {
  PyObject* byteArray;
  if (!PyArg_ParseTuple(args, "O", &byteArray)) {
    PyErr_SetString(PyExc_TypeError, "argument 1 should be a byte array");
    return nullptr;
  }
  Py_INCREF(byteArray);
  AutoPyObject byteArrayScoped(byteArray);
  return Detect(self, byteArray);
}

void initpyandroidfacedetector(void) {
  PyObject* m;

  if (PyType_Ready(&PyFaceDetector_Type) < 0)
    return;
  if (PyType_Ready(&PyFaceData_Type) < 0)
    return;
  m = Py_InitModule3("pyandroidfacedetector", nullptr,
                     "Android Face Detector.");

  Py_INCREF(&PyFaceDetector_Type);
  Py_INCREF(&PyFaceData_Type);
  PyModule_AddObject(m, "FaceDetector", (PyObject*)&PyFaceDetector_Type);

  return;
}
