from distutils.core import setup, Extension

sources = (
'pyentry.cc',
'neven/Embedded/common/src/b_APIEm/DCR.c',
'neven/Embedded/common/src/b_APIEm/BFFaceFinder.c',
'neven/Embedded/common/src/b_APIEm/FaceFinder.c',
'neven/Embedded/common/src/b_APIEm/FaceFinderRef.c',
'neven/Embedded/common/src/b_APIEm/Functions.c',
'neven/Embedded/common/src/b_BasicEm/APh.c',
'neven/Embedded/common/src/b_BasicEm/APhArr.c',
'neven/Embedded/common/src/b_BasicEm/Complex.c',
'neven/Embedded/common/src/b_BasicEm/ComplexArr.c',
'neven/Embedded/common/src/b_BasicEm/Context.c',
'neven/Embedded/common/src/b_BasicEm/DynMemManager.c',
'neven/Embedded/common/src/b_BasicEm/Functions.c',
'neven/Embedded/common/src/b_BasicEm/Int16Arr.c',
'neven/Embedded/common/src/b_BasicEm/Int32Arr.c',
'neven/Embedded/common/src/b_BasicEm/Int8Arr.c',
'neven/Embedded/common/src/b_BasicEm/MathSSE2.c',
'neven/Embedded/common/src/b_BasicEm/MemSeg.c',
'neven/Embedded/common/src/b_BasicEm/MemTbl.c',
'neven/Embedded/common/src/b_BasicEm/Memory.c',
'neven/Embedded/common/src/b_BasicEm/Phase.c',
'neven/Embedded/common/src/b_BasicEm/String.c',
'neven/Embedded/common/src/b_BasicEm/UInt16Arr.c',
'neven/Embedded/common/src/b_BasicEm/UInt32Arr.c',
'neven/Embedded/common/src/b_BasicEm/UInt8Arr.c',
'neven/Embedded/common/src/b_BitFeatureEm/BitParam.c',
'neven/Embedded/common/src/b_BitFeatureEm/Feature.c',
'neven/Embedded/common/src/b_BitFeatureEm/Functions.c',
'neven/Embedded/common/src/b_BitFeatureEm/I04Dns2x2Ftr.c',
'neven/Embedded/common/src/b_BitFeatureEm/I04Dns2x4Ftr.c',
'neven/Embedded/common/src/b_BitFeatureEm/I04Tld2x4Ftr.c',
'neven/Embedded/common/src/b_BitFeatureEm/L01Dns2x4Ftr.c',
'neven/Embedded/common/src/b_BitFeatureEm/L01Tld1x1Ftr.c',
'neven/Embedded/common/src/b_BitFeatureEm/L01Tld2x4Ftr.c',
'neven/Embedded/common/src/b_BitFeatureEm/L04Dns2x2Ftr.c',
'neven/Embedded/common/src/b_BitFeatureEm/L04Dns2x4Ftr.c',
'neven/Embedded/common/src/b_BitFeatureEm/L04Dns3x3Ftr.c',
'neven/Embedded/common/src/b_BitFeatureEm/L04Tld2x4Ftr.c',
'neven/Embedded/common/src/b_BitFeatureEm/L06Dns3x3Ftr.c',
'neven/Embedded/common/src/b_BitFeatureEm/L06Dns4x4Ftr.c',
'neven/Embedded/common/src/b_BitFeatureEm/L06DnsNx4x4Ftr.c',
'neven/Embedded/common/src/b_BitFeatureEm/LocalScanDetector.c',
'neven/Embedded/common/src/b_BitFeatureEm/LocalScanner.c',
'neven/Embedded/common/src/b_BitFeatureEm/ScanDetector.c',
'neven/Embedded/common/src/b_BitFeatureEm/Scanner.c',
'neven/Embedded/common/src/b_BitFeatureEm/Sequence.c',
'neven/Embedded/common/src/b_ImageEm/APhImage.c',
'neven/Embedded/common/src/b_ImageEm/ComplexImage.c',
'neven/Embedded/common/src/b_ImageEm/Flt16Image.c',
'neven/Embedded/common/src/b_ImageEm/Functions.c',
'neven/Embedded/common/src/b_ImageEm/HistoEq.c',
'neven/Embedded/common/src/b_ImageEm/UInt16ByteImage.c',
'neven/Embedded/common/src/b_ImageEm/UInt16BytePyrImage.c',
'neven/Embedded/common/src/b_ImageEm/UInt8Image.c',
'neven/Embedded/common/src/b_ImageEm/UInt32Image.c',
'neven/Embedded/common/src/b_ImageEm/UInt8PyramidalImage.c',
'neven/Embedded/common/src/b_TensorEm/Alt.c',
'neven/Embedded/common/src/b_TensorEm/Cluster2D.c',
'neven/Embedded/common/src/b_TensorEm/Cluster3D.c',
'neven/Embedded/common/src/b_TensorEm/CompactAlt.c',
'neven/Embedded/common/src/b_TensorEm/CompactMat.c',
'neven/Embedded/common/src/b_TensorEm/Flt16Alt2D.c',
'neven/Embedded/common/src/b_TensorEm/Flt16Alt3D.c',
'neven/Embedded/common/src/b_TensorEm/Flt16Mat2D.c',
'neven/Embedded/common/src/b_TensorEm/Flt16Mat3D.c',
'neven/Embedded/common/src/b_TensorEm/Flt16Vec.c',
'neven/Embedded/common/src/b_TensorEm/Flt16Vec2D.c',
'neven/Embedded/common/src/b_TensorEm/Flt16Vec3D.c',
'neven/Embedded/common/src/b_TensorEm/Functions.c',
'neven/Embedded/common/src/b_TensorEm/IdCluster2D.c',
'neven/Embedded/common/src/b_TensorEm/Int16Mat2D.c',
'neven/Embedded/common/src/b_TensorEm/Int16Rect.c',
'neven/Embedded/common/src/b_TensorEm/Int16Vec2D.c',
'neven/Embedded/common/src/b_TensorEm/Int16Vec3D.c',
'neven/Embedded/common/src/b_TensorEm/Int32Mat.c',
'neven/Embedded/common/src/b_TensorEm/MapSequence.c',
'neven/Embedded/common/src/b_TensorEm/Mat.c',
'neven/Embedded/common/src/b_TensorEm/Normalizer.c',
'neven/Embedded/common/src/b_TensorEm/RBFMap2D.c',
'neven/Embedded/common/src/b_TensorEm/SubVecMap.c',
'neven/Embedded/common/src/b_TensorEm/Uint32Rect.c',
'neven/Embedded/common/src/b_TensorEm/VectorMap.c',
'neven/FaceRecEm/common/src/b_FDSDK/DCR.c',
'neven/FaceRecEm/common/src/b_FDSDK/FaceFinder.c',
'neven/FaceRecEm/common/src/b_FDSDK/SDK.c'
)

include_dirs = (
'neven/FaceRecEm/common/src/b_FDSDK',
'neven/FaceRecEm/common/src',
'neven/Embedded/common/conf',
'neven/Embedded/common/src',
'neven/unix/src'
)

module1 = Extension('demo',
                    define_macros = [('MAJOR_VERSION', '1'),
                                     ('MINOR_VERSION', '0')],
                    include_dirs = ['/usr/local/include'],
                    libraries = ['m'],
                    library_dirs = include_dirs,
                    sources = sources)

setup (name = 'AndroidFaceDetector',
       version = '0.1',
       description = "Detect faces using android's approach",
       author = 'linzj',
       author_email = 'manjian2006@gmail.com',
       long_description = '''
Detect faces using android's approach.
''',
       ext_modules = [module1])
