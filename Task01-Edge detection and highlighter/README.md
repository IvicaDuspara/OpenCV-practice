#Task 01 - Edge detection and highlighter

[1. Running](#Run)

This program shows an example of how image filtering affects
edge detection.

<a name="Run"></a>
##Running

Program takes two arguments which is:
1. Path, which can be:
    + Absolute/relative path to an image you want to test
    + 1 - Loads first resource image
    + 2 - Loads second resource image
2. Working mode which can be:
    + 1 - Edge detection
    + 2 - Highlighter
```
username@user: ~$ ./Task01 1 1
```

![Alt text](./resources/usage1.png?raw=true "Edge detection with no blur")
*Figure 1 - No blur and both thresholds set to 0 in Canny edge detection*

![Alt text](./resources/usage2.png?raw=true "Edge detection with blur and threshholds")
*Figure 2 - Added blur and thresholds*

```
username@user: ~$ ./Task01 1 2
```

![Alt text](./resources/usage3.png?raw=true "Highlight")
*Figure 3 - Highlight object test*