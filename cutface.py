import AndroidFaceDetector, Image, sys, glob, os.path
import multiprocessing

count = multiprocessing.Value('i', 0)
class MultiProcessHandler(object):
    def __init__(self, func):
        self.cpu_count = multiprocessing.cpu_count()
        self.pool = multiprocessing.Pool(self.cpu_count)
        self.func = func

    def submitJob(self, _list):
        self.pool.map_async(self.func, _list)
        self.pool.close()

    def join(self):
        self.pool.join()


def getFileName(f):
    global count
    ext = os.path.splitext(f)[1]
    with count.get_lock():
        c1 = count.value
        count.value += 1
    return "{0}{1}".format(c1, ext)

def getFaceBound(imageSize, faceData):
    rect = [faceData.midpointx - 1.2 * faceData.eyedist,
            faceData.midpointy - 1.5 * faceData.eyedist,
            faceData.midpointx + 1.2 * faceData.eyedist,
            faceData.midpointy + 2.0 * faceData.eyedist]
    width, height = imageSize
    if rect[2] > width:
        offset = rect[2] - width
        rect[0] -= offset
        rect[2] = width

    if rect[3] > height:
        offset = rect[3] - width
        rect[3] -= offset
        rect[3] = height
    return rect

def cutFace(image, bound):
    bound = [int(b) for b in bound]
    width = bound[2] - bound[0]
    height = bound[3] - bound[1]
    newImage = image.transform((width, height), Image.EXTENT, bound)
    return newImage

def canonicalize(image):
    newImage = image.resize((44, 64), Image.ANTIALIAS)
    return newImage

def saveFace(image, f):
    fileName = getFileName(f)
    if image.mode == 'P':
        image = image.convert('RGB')
    image.save('/tmp/' + fileName)

def saveFaces(image, getFace, numOfFaces, f):
    for i in range(numOfFaces):
        faceData = getFace(i)
        if faceData.confidence > 0.51:
            faceImage = cutFace(image, getFaceBound(image.size, faceData))
            faceImage = canonicalize(faceImage)
            saveFace(faceImage, f)

def handleFile(f):
    image = Image.open(f)
    numOfFaces = detector.detect(image)
    if 0 == numOfFaces:
        print >>sys.stderr, 'no face detected in %s' % (f)
    else:
        saveFaces(image, detector.getFace, numOfFaces, f)

if __name__ == '__main__':
    detector = AndroidFaceDetector.AndroidFaceDetectorWrapper(1024, 1024, 3)
    if len(sys.argv) <= 1:
        print >>sys.stderr, 'need a file name'
        sys.exit(1);

    fileList = []
    for pattern in sys.argv[1:]:
        for f in glob.glob(pattern):
            fileList.append(f)
    handler = MultiProcessHandler(handleFile)
    handler.submitJob(fileList)
    handler.join()
