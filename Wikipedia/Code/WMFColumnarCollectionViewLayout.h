@import UIKit;
@class WMFCVLMetrics;

/*!
 @class        WMFColumnarCollectionViewLayout
 @abstract     A WMFColumnarCollectionViewLayout organizes a collection view into columns grouped by section - all items from the same section will be in the same column.
 @discussion   ...
 */
@interface WMFColumnarCollectionViewLayout : UICollectionViewLayout

@property (nonatomic) BOOL slideInNewContentFromTheTop;
@property (nonatomic, readonly) UIEdgeInsets readableMargins;

- (CGFloat)layoutHeightForWidth:(CGFloat)width;

@end

struct WMFLayoutEstimate {
    BOOL precalculated;
    CGFloat height;
};
typedef struct WMFLayoutEstimate WMFLayoutEstimate;

@protocol WMFColumnarCollectionViewLayoutDelegate <UICollectionViewDelegate>
@required
- (WMFLayoutEstimate)collectionView:(nonnull UICollectionView *)collectionView estimatedHeightForItemAtIndexPath:(nonnull NSIndexPath *)indexPath forColumnWidth:(CGFloat)columnWidth;
- (WMFLayoutEstimate)collectionView:(nonnull UICollectionView *)collectionView estimatedHeightForHeaderInSection:(NSInteger)section forColumnWidth:(CGFloat)columnWidth;
- (WMFLayoutEstimate)collectionView:(nonnull UICollectionView *)collectionView estimatedHeightForFooterInSection:(NSInteger)section forColumnWidth:(CGFloat)columnWidth;
- (BOOL)collectionView:(nonnull UICollectionView *)collectionView prefersWiderColumnForSectionAtIndex:(NSUInteger)index;

- (nonnull WMFCVLMetrics *)metricsWithBoundsSize:(CGSize)size readableWidth:(CGFloat)readableWidth layoutMargins:(UIEdgeInsets)layoutMargins;

@end
