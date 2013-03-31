// check feasibility
// for two intervals opposite, if overlap, then dead
// suppose no two opposite intervals overlap, then they are independent
// we can work with two sets, one forward and one backward
// For same direction set, if one interval is fully contained in another, then dead
// if not, then there is a ways to do the transformation
// select the farthest one (closest to the goal) and move to the goal
