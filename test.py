import AndroidFaceDetector, Image, sys, ImageDraw, ImageFont, glob, os.path
fontHeight = 40
font = ImageFont.truetype('/usr/./share/fonts/truetype/dejavu/DejaVuSerif.ttf', fontHeight)

def drawPoint(draw, x, y, pointsize, color):
    draw.ellipse((x - pointsize, y - pointsize,
                 x + pointsize, y + pointsize),
                 fill=color)

def saveImage(image, getFace, numOfFaces, f):
    toshow = Image.new('RGBA', (image.width, image.height))
    toshow.paste(image, (0, 0))
    draw = ImageDraw.Draw(toshow)
    pointsize = 5
    colors = ('red', 'blue', 'green',
             'pink', 'purple', 'white')
    p = 0
    position = 0
    shouldSave = False
    for i in range(numOfFaces):
        faceData = getFace(i)
        if faceData.confidence > 0.51:
            shouldSave = True
            colorIndex = i % len(colors)
            color = colors[colorIndex]
            drawPoint(draw, faceData.midpointx, faceData.midpointy, pointsize, color)
            rect = (faceData.midpointx - 1 * faceData.eyedist,
                    faceData.midpointy - 1 * faceData.eyedist,
                    faceData.midpointx + 1 * faceData.eyedist,
                    faceData.midpointy + 1 * faceData.eyedist)
            draw.rectangle(rect, outline=color)
            draw.text((0, position), 'confidence: {0}, eyedist: {1}'.format(faceData.confidence, faceData.eyedist), fill=color, font=font)
            position += fontHeight + 5

    # get save name
    if shouldSave:
        save_path = '/tmp/' + os.path.basename(f) + 'detected.jpg'
        print 'saving file: ' + save_path
        toshow.save(save_path)

if __name__ == '__main__':
    detector = AndroidFaceDetector.AndroidFaceDetectorWrapper(1024, 1024, 3)
    if len(sys.argv) <= 1:
        print >>sys.stderr, 'need a file name'
        sys.exit(1);
    for pattern in sys.argv[1:]:
        for f in glob.glob(pattern):
            image = Image.open(f)
            numOfFaces = detector.detect(image)
            if 0 == numOfFaces:
                print >>sys.stderr, 'no face detected in %s' % (f)
            else:
                saveImage(image, detector.getFace, numOfFaces, f)
