import sys, pyandroidfacedetector, Image

class AndroidFaceDetectorWrapper(object):
    def __init__(self, width, height, maxFaces):
        module = (sys.modules[__name__])
        moduleFile = module.__file__[:module.__file__.rindex('/')] + '/neven/Embedded/common/data/APIEm/Modules'
        self.detector = pyandroidfacedetector.FaceDetector(moduleFile, width, height, maxFaces)
        self.width = width
        self.height = height
        self.offsets = (0, 0)
        self.scale = 1.0

    def rescaleIfNeeded(self, image):
        if image.width > self.width:
            self.scale = float(self.width) / image.width
        elif image.height > self.height:
            self.scale = float(self.height) / image.height
        if self.scale != 1.0:
            resize = (int(image.width * self.scale), int(image.height * self.scale))
            return image.resize(resize, Image.ANTIALIAS)
        return image

    def detect(self, image):
        image = self.rescaleIfNeeded(image)
        # Find midpoint
        width, height = image.size
        width /= 2
        height /= 2
        # Find offset
        self.offsets = (self.width / 2 - width, self.height / 2 - height)
        imageScreen = Image.new('RGB', (self.width, self.height), 'white')
        imageScreen.paste(image, self.offsets)
        imageScreen = imageScreen.convert('L')
        return self.detector.Detect(imageScreen.tobytes())

    def getFace(self, index):
        face = self.detector.GetFace(index)
        print(face.midpointx, face.midpointy)
        face.midpointx = (face.midpointx - self.offsets[0]) / self.scale
        face.midpointy = (face.midpointy - self.offsets[1]) / self.scale
        face.eyedist = (face.eyedist) / self.scale
        print(face.midpointx, face.midpointy)
        return face

