// try all 9! permutations if we label from top down and left to right
// for each perm, try to find two horizontal lines to get
// a[0] + a[1] + a[2]
// a[3] + a[4] + a[5]
// a[6] + a[7] + a[8]
// and then two vertical lines to get column sums correct
//
// The lines are obtained by binary search
// since x[i], y[i] are integers, we only need split lines to be in
// integer or .5 places
//
// time: 9! * log(10^9) = 10^6 * 30 = 10^7
/////////////////////////////////////////////////////////////////////
