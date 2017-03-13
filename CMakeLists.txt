CMAKE_MINIMUM_REQUIRED( VERSION 3.0 )

PROJECT( glplayground )

IF( WIN32 )

    SET( PLATFORM_LIBS opengl32 glu32)
    #SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

ELSEIF( APPLE )

    # Create a nibless project per http://blog.hyperjeff.net/code?id=292
    
    #FILE( GLOB PEZ
    #    lib/libpez/pez.h
    #    lib/libpez/pez.cocoa.m
    #)

    FIND_LIBRARY( COCOA_LIBRARY Cocoa )

    #SET( PLATFORM_LIBS
    #    ${COCOA_LIBRARY}
    #    /System/Library/Frameworks/OpenGL.framework )

ELSEIF( UNIX )

    #FIND_PACKAGE(OpenGL REQUIRED)
    #INCLUDE_DIRECTORIES(${OpenGL_INCLUDE_DIRS})
    #LINK_DIRECTORIES(${OpenGL_LIBRARY_DIRS})
    #ADD_DEFINITIONS(${OpenGL_DEFINITIONS})
    #if(NOT OPENGL_FOUND)
    #    MESSAGE(ERROR " OPENGL not found!")
    #endif(NOT OPENGL_FOUND)

    #SET(PLATFORM_LIBS ${OPENGL_LIBRARIES} X11 m)
    SET(PLATFORM_LIBS m)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)
    SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS)

ENDIF()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(SRCS
       neven/Embedded/common/src/b_APIEm/DCR.c
       neven/Embedded/common/src/b_APIEm/BFFaceFinder.c
       neven/Embedded/common/src/b_APIEm/FaceFinder.c
       neven/Embedded/common/src/b_APIEm/FaceFinderRef.c
       neven/Embedded/common/src/b_APIEm/Functions.c
       neven/Embedded/common/src/b_BasicEm/APh.c
       neven/Embedded/common/src/b_BasicEm/APhArr.c
       neven/Embedded/common/src/b_BasicEm/Complex.c
       neven/Embedded/common/src/b_BasicEm/ComplexArr.c
       neven/Embedded/common/src/b_BasicEm/Context.c
       neven/Embedded/common/src/b_BasicEm/DynMemManager.c
       neven/Embedded/common/src/b_BasicEm/Functions.c
       neven/Embedded/common/src/b_BasicEm/Int16Arr.c
       neven/Embedded/common/src/b_BasicEm/Int32Arr.c
       neven/Embedded/common/src/b_BasicEm/Int8Arr.c
       neven/Embedded/common/src/b_BasicEm/MathSSE2.c
       neven/Embedded/common/src/b_BasicEm/MemSeg.c
       neven/Embedded/common/src/b_BasicEm/MemTbl.c
       neven/Embedded/common/src/b_BasicEm/Memory.c
       neven/Embedded/common/src/b_BasicEm/Phase.c
       neven/Embedded/common/src/b_BasicEm/String.c
       neven/Embedded/common/src/b_BasicEm/UInt16Arr.c
       neven/Embedded/common/src/b_BasicEm/UInt32Arr.c
       neven/Embedded/common/src/b_BasicEm/UInt8Arr.c
       neven/Embedded/common/src/b_BitFeatureEm/BitParam.c
       neven/Embedded/common/src/b_BitFeatureEm/Feature.c
       neven/Embedded/common/src/b_BitFeatureEm/Functions.c
       neven/Embedded/common/src/b_BitFeatureEm/I04Dns2x2Ftr.c
       neven/Embedded/common/src/b_BitFeatureEm/I04Dns2x4Ftr.c
       neven/Embedded/common/src/b_BitFeatureEm/I04Tld2x4Ftr.c
       neven/Embedded/common/src/b_BitFeatureEm/L01Dns2x4Ftr.c
       neven/Embedded/common/src/b_BitFeatureEm/L01Tld1x1Ftr.c
       neven/Embedded/common/src/b_BitFeatureEm/L01Tld2x4Ftr.c
       neven/Embedded/common/src/b_BitFeatureEm/L04Dns2x2Ftr.c
       neven/Embedded/common/src/b_BitFeatureEm/L04Dns2x4Ftr.c
       neven/Embedded/common/src/b_BitFeatureEm/L04Dns3x3Ftr.c
       neven/Embedded/common/src/b_BitFeatureEm/L04Tld2x4Ftr.c
       neven/Embedded/common/src/b_BitFeatureEm/L06Dns3x3Ftr.c
       neven/Embedded/common/src/b_BitFeatureEm/L06Dns4x4Ftr.c
       neven/Embedded/common/src/b_BitFeatureEm/L06DnsNx4x4Ftr.c
       neven/Embedded/common/src/b_BitFeatureEm/LocalScanDetector.c
       neven/Embedded/common/src/b_BitFeatureEm/LocalScanner.c
       neven/Embedded/common/src/b_BitFeatureEm/ScanDetector.c
       neven/Embedded/common/src/b_BitFeatureEm/Scanner.c
       neven/Embedded/common/src/b_BitFeatureEm/Sequence.c
       neven/Embedded/common/src/b_ImageEm/APhImage.c
       neven/Embedded/common/src/b_ImageEm/ComplexImage.c
       neven/Embedded/common/src/b_ImageEm/Flt16Image.c
       neven/Embedded/common/src/b_ImageEm/Functions.c
       neven/Embedded/common/src/b_ImageEm/HistoEq.c
       neven/Embedded/common/src/b_ImageEm/UInt16ByteImage.c
       neven/Embedded/common/src/b_ImageEm/UInt16BytePyrImage.c
       neven/Embedded/common/src/b_ImageEm/UInt8Image.c
       neven/Embedded/common/src/b_ImageEm/UInt32Image.c
       neven/Embedded/common/src/b_ImageEm/UInt8PyramidalImage.c
       neven/Embedded/common/src/b_TensorEm/Alt.c
       neven/Embedded/common/src/b_TensorEm/Cluster2D.c
       neven/Embedded/common/src/b_TensorEm/Cluster3D.c
       neven/Embedded/common/src/b_TensorEm/CompactAlt.c
       neven/Embedded/common/src/b_TensorEm/CompactMat.c
       neven/Embedded/common/src/b_TensorEm/Flt16Alt2D.c
       neven/Embedded/common/src/b_TensorEm/Flt16Alt3D.c
       neven/Embedded/common/src/b_TensorEm/Flt16Mat2D.c
       neven/Embedded/common/src/b_TensorEm/Flt16Mat3D.c
       neven/Embedded/common/src/b_TensorEm/Flt16Vec.c
       neven/Embedded/common/src/b_TensorEm/Flt16Vec2D.c
       neven/Embedded/common/src/b_TensorEm/Flt16Vec3D.c
       neven/Embedded/common/src/b_TensorEm/Functions.c
       neven/Embedded/common/src/b_TensorEm/IdCluster2D.c
       neven/Embedded/common/src/b_TensorEm/Int16Mat2D.c
       neven/Embedded/common/src/b_TensorEm/Int16Rect.c
       neven/Embedded/common/src/b_TensorEm/Int16Vec2D.c
       neven/Embedded/common/src/b_TensorEm/Int16Vec3D.c
       neven/Embedded/common/src/b_TensorEm/Int32Mat.c
       neven/Embedded/common/src/b_TensorEm/MapSequence.c
       neven/Embedded/common/src/b_TensorEm/Mat.c
       neven/Embedded/common/src/b_TensorEm/Normalizer.c
       neven/Embedded/common/src/b_TensorEm/RBFMap2D.c
       neven/Embedded/common/src/b_TensorEm/SubVecMap.c
       neven/Embedded/common/src/b_TensorEm/Uint32Rect.c
       neven/Embedded/common/src/b_TensorEm/VectorMap.c
       neven/FaceRecEm/common/src/b_FDSDK/DCR.c
       neven/FaceRecEm/common/src/b_FDSDK/FaceFinder.c
       neven/FaceRecEm/common/src/b_FDSDK/SDK.c
)
#FILE( GLOB SQUISH_SRC squish/*.h squish/*.cpp )
#FILE( GLOB GLSW_SRC lib/glsw/*.c lib/glsw/*.h )

#INCLUDE_DIRECTORIES(freeglut-3.0.0/include glew-1.13.0/include)


ADD_LIBRARY( pyandroidfacedetector SHARED ${SRCS})
TARGET_LINK_LIBRARIES( pyandroidfacedetector ${PLATFORM_LIBS})
TARGET_INCLUDE_DIRECTORIES( pyandroidfacedetector
    PRIVATE
	neven/FaceRecEm/common/src/b_FDSDK
	neven/FaceRecEm/common/src
	neven/Embedded/common/conf
	neven/Embedded/common/src
	neven/unix/src
)

FILE(COPY neven/Embedded/common/data/APIEm/Modules/RFFspeed_501.bmd DESTINATION ${CMAKE_SOURCE_DIR}/bin)

FILE(COPY neven/Embedded/common/data/APIEm/Modules/RFFstd_501.bmd DESTINATION ${CMAKE_SOURCE_DIR}/bin)

ADD_CUSTOM_TARGET(debug ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE:STRING=Debug ${PROJECT_SOURCE_DIR})
ADD_CUSTOM_TARGET(release ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE:STRING=Release ${PROJECT_SOURCE_DIR})
