#include <Python.h>
#include <stdlib.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using std::string;

extern "C" {
#include <fd_emb_sdk.h>
void initpyandroidfacedetector(void);
}

struct FaceData {
  float confidence;
  float midpointx;
  float midpointy;
  float eyedist;
};

class AutoPyObject {
 public:
  explicit AutoPyObject(PyObject*);
  ~AutoPyObject();
  AutoPyObject(AutoPyObject&) = delete;
  AutoPyObject& operator=(AutoPyObject&) = delete;
  AutoPyObject(AutoPyObject&&);
  AutoPyObject& operator=(AutoPyObject&&);
  operator PyObject*();

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

template <typename T>
AutoPyObject makeAutoPyObject(T* o) {
  AutoPyObject ao((PyObject*)o);
  return ao;
}

AutoPyObject::operator PyObject*() {
  return o_;
}

static void getFaceData(btk_HDCR hdcr, FaceData* fdata) {
  btk_Node leftEye, rightEye;

  btk_DCR_getNode(hdcr, 0, &leftEye);
  btk_DCR_getNode(hdcr, 1, &rightEye);

  fdata->eyedist = (float)(rightEye.x - leftEye.x) / (1 << 16);
  fdata->midpointx = (float)(rightEye.x + leftEye.x) / (1 << 17);
  fdata->midpointy = (float)(rightEye.y + leftEye.y) / (1 << 17);
  fdata->confidence = (float)btk_DCR_confidence(hdcr) / (1 << 24);
}

static void doThrowNoMemory(const char* msg) {
  PyErr_SetString(PyExc_MemoryError, msg);
}

static PyObject* initialize(PyObject* module, int w, int h, int maxFaces) {
  // load the configuration file
  const char* modulePath = "./neven/Embedded/common/data/APIEm/Modules";
  if (!modulePath)
    return nullptr;
  string path(modulePath);
  path.append("/RFFstd_501.bmd");
  // path.appendPath("usr/share/bmd/RFFspeed_501.bmd");

  const int MAX_FILE_SIZE = 65536;
  void* initData = malloc(MAX_FILE_SIZE); /* enough to fit entire file */
  int filedesc = open(path.c_str(), O_RDONLY);
  int initDataSize = read(filedesc, initData, MAX_FILE_SIZE);
  close(filedesc);

  // --------------------------------------------------------------------
  btk_HSDK sdk = nullptr;
  btk_SDKCreateParam sdkParam = btk_SDK_defaultParam();
  sdkParam.fpMalloc = malloc;
  sdkParam.fpFree = free;
  sdkParam.maxImageWidth = w;
  sdkParam.maxImageHeight = h;

  btk_Status status = btk_SDK_create(&sdkParam, &sdk);
  // make sure everything went well
  if (status != btk_STATUS_OK) {
    // XXX: be more precise about what went wrong
    doThrowNoMemory("btk_SDK_create failed");
    return nullptr;
  }

  btk_HDCR dcr = NULL;
  btk_DCRCreateParam dcrParam = btk_DCR_defaultParam();
  btk_DCR_create(sdk, &dcrParam, &dcr);

  btk_HFaceFinder fd = NULL;
  btk_FaceFinderCreateParam fdParam = btk_FaceFinder_defaultParam();
  fdParam.pModuleParam = initData;
  fdParam.moduleParamSize = initDataSize;
  fdParam.maxDetectableFaces = maxFaces;
  status = btk_FaceFinder_create(sdk, &fdParam, &fd);
  btk_FaceFinder_setRange(fd, 20, w / 2); /* set eye distance range */

  // make sure everything went well
  if (status != btk_STATUS_OK) {
    // XXX: be more precise about what went wrong
    fprintf(stderr, "btk_FaceFinder_create failed: %d.\n", status);
    doThrowNoMemory("btk_FaceFinder_create failed");
    return nullptr;
  }

  // free the configuration file
  free(initData);

  // initialize the java object
  PyObject_SetAttrString(module, "fd",
                         makeAutoPyObject(PyLong_FromLong((long)fd)));
  PyObject_SetAttrString(module, "sdk",
                         makeAutoPyObject(PyLong_FromLong((long)sdk)));
  PyObject_SetAttrString(module, "dcr",
                         makeAutoPyObject(PyLong_FromLong((long)dcr)));

  return nullptr;
}

static char initialize_docs[] = "initialize( ): initialize sdk\n";

static PyMethodDef helloworld_funcs[] = {
    // {"initialize", (PyCFunction)initialize, METH_NOARGS, initialize_docs},
    {nullptr}};

void initpyandroidfacedetector(void) {
  PyObject* m = Py_InitModule3("pyandroidfacedetector", helloworld_funcs,
                               "Android Face Detector");
  initialize(m, 1024, 1024, 1);
}
