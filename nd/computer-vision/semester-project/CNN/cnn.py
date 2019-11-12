def find_bboxes(features, lower, upper):
    return [f.bbox for f in features if lower < f.bbox_area and f.bbox_area < upper]

def plot_bboxes(img, features, lower, upper):
    bboxes = []
    fig, ax = plt.subplots()
    ax.imshow(img, cmap=plt.cm.gray)
    for f in features:
        if lower < f.bbox_area and f.bbox_area < upper:
            bboxes.append(f.bbox)
            x1, y1, x2, y2 = f.bbox
            y, x = f.centroid
            rect = patches.Rectangle((y1, x1), y2 - y1, x2 - x1, linewidth=1, edgecolor='r', fill=False)
            ax.add_patch(rect)
            ax.plot(x, y, '.g', markersize=1)
    plt.show()
    return bboxes

def main():
    return 0

with warnings.catch_warnings():
    warnings.simplefilter('ignore')
    main()
