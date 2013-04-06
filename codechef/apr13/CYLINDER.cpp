// start with W x H
//
// cut into two pieces, either both have W or both have H
//
// cut one piece into two identical circles, pi*R*R
//
// cut the other piece into rectangle width = 2*pi*R, height = A
//
// to maximize: VOL = pi*R*R*A

// T = 4*10^5
// W, H = 10^6 -1
//
// binary search for the cut
//
// after cut, left or right to make circle
// circle bigger ...

// given A and R, can they fit into W x H paper?
//
// three pieces: two squares of R x R and one rectangle of A x R
//
// could be circle, circle, rect
// or
// circle rect
// circle
//
// so the problem is to fit in two pieces, 2R x R and A x R
// or R x 2R and A x R
//
// the goal is to maximize R*R*A
//

// option 1: 2R x R and A x R, and use W x H
// 2R + A <= W
// R + R  <= H
//
// to maximize R*R*A <= R*R*(W - 2R)
// we know R <= H / 2.0 and R <= W / 2.0 since A >= 0
// so R <= min(H, W) / 2.0
//
// In this case must have W > H
// Take derivative, 2WR - 2*3R^2 = 0, 2W - 6R = 0, R = W / 3.0

// Overall not too bad, just case analysis
