import AndroidFaceDetector, Image, sys, ImageDraw

def showImage(image, faceData):
    toshow = Image.new('RGB', (image.width, image.height))
    toshow.paste(image, (0, 0))
    draw = ImageDraw.Draw(toshow)
    pointsize = 5
    draw.ellipse((faceData.midpointx - pointsize, faceData.midpointy - pointsize,
                 faceData.midpointx + pointsize, faceData.midpointy + pointsize),
                 fill=(255, 0, 0))
    toshow.show()

if __name__ == '__main__':
    detector = AndroidFaceDetector.AndroidFaceDetectorWrapper(1024, 1024, 2)
    if len(sys.argv) != 2:
        print >>sys.stderr, 'need a file name'
        sys.exit(1);
    image = Image.open(sys.argv[1])
    if 0 == detector.detect(image):
        print >>sys.stderr, 'no face detected in %s' % (sys.argv[1])
    else:
        showImage(image, detector.getFace(0))
