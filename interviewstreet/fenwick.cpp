// Author: Piotr Tarsa
// License: Public Domain

//#define NDEBUG

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int32_t max(int32_t const a, int32_t const b) {
    return a < b ? b : a;
}

bool equal(int32_t const a, int32_t const b, int32_t const c) {
    return a == b && b == c;
}

void makeLogTable(uint8_t * const table, int32_t const length) {
    assert(table != NULL);
    assert(length >= 0);
    if (length == 0)
        return;
    table[0] = 0;
    for (int32_t i = 1; i < length; i++)
        table[i] = 1 + table[i >> 1];
}

uint8_t computeLog(uint8_t(* const table)[256], uint32_t const value) {
    if (value < 0x10000ul) {
        if (value < 0x100ul)
            return (*table)[value];
        else
            return (*table)[value >> 8] + 8;
    } else {
        if (value < 0x1000000ul)
            return (*table)[value >> 16 & 0xff] + 16;
        else
            return (*table)[value >> 24 & 0xff] + 24;
    }
}

typedef struct {
    int32_t items;
    int32_t *at;
} frequencies_t;

frequencies_t makeFrequencies(int32_t const items) {
    frequencies_t frequencies;
    frequencies.items = items;
    frequencies.at = malloc(sizeof (int32_t) * items);
    memset(frequencies.at, 0, sizeof (int32_t) * items);
    return frequencies;
}

bool isNonDecreasing1(frequencies_t const * const frequencies) {
    for (int32_t i = 0; i < frequencies->items; i++)
        if (frequencies->at[i] < 0)
            return false;
    return true;
}

int32_t getFrequency1(frequencies_t const * const frequencies,
        int32_t const item) {
    assert(item >= 0);
    assert(item < frequencies->items);
    return frequencies->at[item];
}

void adjustFrequency1(frequencies_t * const frequencies,
        int32_t const item, int32_t const value) {
    assert(item >= 0);
    assert(item < frequencies->items);
    frequencies->at[item] += value;
}

int32_t getCumulativeInclusive1(frequencies_t const * const frequencies,
        int32_t const item) {
    assert(item >= 0);
    assert(item < frequencies->items);
    int32_t result = 0;
    for (int32_t i = 0; i <= item; i++)
        result += frequencies->at[i];
    return result;
}

int32_t getTotal1(frequencies_t const * const frequencies) {
    return getCumulativeInclusive1(frequencies, frequencies->items - 1);
}

int32_t getCumulativeExclusive1(frequencies_t const * const frequencies,
        int32_t const item) {
    assert(item >= 0);
    assert(item < frequencies->items);
    int32_t result = 0;
    for (int32_t i = 0; i < item; i++)
        result += frequencies->at[i];
    return result;
}

void adjustRangeByValue1(frequencies_t * const frequencies,
        int32_t const from, int32_t const to, int32_t const value) {
    assert(from >= 0);
    assert(from <= to);
    assert(to < frequencies->items);
    for (int32_t i = from; i <= to; i++)
        frequencies->at[i] += value;
}

void rescale1(frequencies_t * const frequencies) {
    for (int32_t i = 0; i < frequencies->items; i++)
        frequencies->at[i] -= frequencies->at[i] >> 1;
}

int32_t findFirstInterval1(frequencies_t const * const frequencies,
        int32_t const value) {
    assert(value >= 0);
    assert(value < getTotal1(frequencies));
    assert(isNonDecreasing1(frequencies));
    int32_t sum = 0;
    for (int32_t i = 0; i < frequencies->items; i++)
        if (frequencies->at[i] + sum > value)
            return i;
        else
            sum += frequencies->at[i];
    return frequencies->items - 1;
}

typedef struct {
    int32_t items;
    int32_t *at;
} cumulative_t;

cumulative_t makeCumulative(int32_t const items) {
    cumulative_t cumulative;
    cumulative.items = items;
    cumulative.at = malloc(sizeof (int32_t) * items);
    memset(cumulative.at, 0, sizeof (int32_t) * items);
    return cumulative;
}

bool isNonDecreasing2(cumulative_t const * const cumulative) {
    for (int32_t i = 1; i < cumulative->items; i++)
        if (cumulative->at[i - 1] > cumulative->at[i])
            return false;
    return true;
}

int32_t getFrequency2(cumulative_t const * const cumulative,
        int32_t const item) {
    assert(item >= 0);
    assert(item < cumulative->items);
    return item == 0 ? cumulative->at[0] :
            cumulative->at[item] - cumulative->at[item - 1];
}

void adjustFrequency2(cumulative_t * const cumulative,
        int32_t const item, int32_t const value) {
    assert(item >= 0);
    assert(item < cumulative->items);
    for (int32_t i = item; i < cumulative->items; i++)
        cumulative->at[i] += value;
}

int32_t getCumulativeInclusive2(
        cumulative_t const * const cumulative,
        int32_t const item) {
    assert(item >= 0);
    assert(item < cumulative->items);
    return cumulative->at[item];
}

int32_t getTotal2(
        cumulative_t const * const cumulative) {
    return getCumulativeInclusive2(cumulative, cumulative->items - 1);
}

int32_t getCumulativeExclusive2(
        cumulative_t const * const cumulative,
        int32_t const item) {
    assert(item >= 0);
    assert(item < cumulative->items);
    return item == 0 ? 0 : cumulative->at[item - 1];
}

void adjustRangeByValue2(cumulative_t * const cumulative,
        int32_t const from, int32_t const to, int32_t const value) {
    assert(from >= 0);
    assert(from <= to);
    assert(to < cumulative->items);
    for (int32_t i = from; i <= to; i++)
        cumulative->at[i] += (i - from + 1) * value;
    for (int32_t i = to + 1; i < cumulative->items; i++)
        cumulative->at[i] += (to - from + 1) * value;
}

void rescale2(cumulative_t * const cumulative) {
    int32_t prev = 0;
    int32_t error = 0;
    for (int32_t i = 0; i < cumulative->items; i++) {
        error += (cumulative->at[i] - prev) & 1;
        prev = cumulative->at[i];
        cumulative->at[i] -= cumulative->at[i] - error >> 1;
    }
}

int32_t findFirstInterval2(cumulative_t const * const cumulative,
        int32_t const value) {
    assert(value >= 0);
    assert(value < getTotal2(cumulative));
    assert(isNonDecreasing2(cumulative));
    int32_t left = 0;
    int32_t right = cumulative->items - 1;
    while (left < right) {
        int32_t const mid = left + right >> 1;
        if (cumulative->at[mid] > value)
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}

typedef struct {
    int32_t items;
    int32_t *at;
} tree_t;

tree_t makeTree(int32_t const items) {
    tree_t tree;
    tree.items = items;
    tree.at = malloc(sizeof (int32_t) * items);
    memset(tree.at, 0, sizeof (int32_t) * items);
    return tree;
}

bool isNonDecreasing3(tree_t const * const tree,
        uint8_t(* const table)[256]) {
    if (tree->items == 0)
        return true;
    int32_t const items = tree->items;
    int32_t const ilog = computeLog(table, items);
    int32_t stackItems[ilog];
    int32_t stackValues[ilog];
    int32_t next = 0;
    for (int32_t i = 0; i < items; i++)
        if (i % 2 == 0) {
            if (tree->at[i] < 0)
                return false;
            if (next == 0 || stackItems[next - 1] != i + 1) {
                stackItems[next] = i + 1;
                stackValues[next] = tree->at[i];
                next++;
            } else
                stackValues[next - 1] += tree->at[i];
        } else {
            if (tree->at[i] - stackValues[next - 1] < 0)
                return false;
            stackValues[next - 1] = tree->at[i];
            stackItems[next - 1] |= stackItems[next - 1] + 1;
            if (next - 1 != 0 && stackItems[next - 2] == stackItems[next - 1]) {
                stackValues[next - 2] += stackValues[next - 1];
                next--;
            }
        }
    return true;
}

int32_t getCumulativeInclusive3(tree_t const * const tree,
        int32_t const item) {
    assert(item >= 0);
    assert(item < tree->items);
    int32_t result = 0;
    int32_t p = item + 1;
    do {
        result += tree->at[p - 1];
        p &= p - 1;
    } while (p > 0);
    return result;
}

int32_t getTotal3(tree_t const * const tree) {
    return getCumulativeInclusive3(tree, tree->items - 1);
}

int32_t getCumulativeExclusive3(tree_t const * const tree,
        int32_t const item) {
    assert(item >= 0);
    assert(item < tree->items);
    int32_t result = 0;
    int32_t p = item;
    while (p > 0) {
        result += tree->at[p - 1];
        p &= p - 1;
    }
    return result;
}

int32_t getFrequency3(tree_t const * const tree,
        int32_t const item) {
    assert(item >= 0);
    assert(item < tree->items);
    int32_t result = tree->at[item];
    int32_t p = 1;
    while ((item & p) > 0) {
        result -= tree->at[item - p];
        p <<= 1;
    }
    return result;
}

void adjustFrequency3(tree_t * const tree,
        int32_t const item, int32_t const value) {
    assert(item >= 0);
    assert(item < tree->items);
    int32_t p = item;
    do {
        tree->at[p] += value;
        p |= p + 1;
    } while (p < tree->items);
}

void adjustRangeByValue3(tree_t * const tree,
        int32_t const from, int32_t const to, int32_t const value) {
    assert(from >= 0);
    assert(from <= to);
    assert(to < tree->items);
    for (int32_t i = from; i < to; i++)
        tree->at[i] += (i - max(from, i & i + 1) + 1) * value;
    int32_t p = to;
    do {
        tree->at[p] += (to - max(from, p & p + 1) + 1) * value;
        p |= p + 1;
    } while (p < tree->items);
}

void rescale3(tree_t * const tree,
        uint8_t(* const table)[256]) {
    int32_t const items = tree->items;
    int32_t const ilog = computeLog(table, items);
    int32_t stackItems[ilog];
    int32_t stackOldValues[ilog];
    int32_t stackNewValues[ilog];
    int32_t next = 0;
    for (int32_t i = 0; i < items; i++)
        if (i % 2 == 0) {
            int32_t const oldValue = tree->at[i];
            /** Rescale function. */
            int32_t const newValue = oldValue - oldValue / 2;
            if (next == 0 || stackItems[next - 1] != i + 1) {
                stackItems[next] = i + 1;
                stackOldValues[next] = oldValue;
                stackNewValues[next] = newValue;
                next++;
            } else {
                stackOldValues[next - 1] += oldValue;
                stackNewValues[next - 1] += newValue;
            }
            tree->at[i] = newValue;
        } else {
            int32_t const oldValue = tree->at[i] - stackOldValues[next - 1];
            /** Rescale function. */
            int32_t const newValue = oldValue - oldValue / 2;
            tree->at[i] = stackNewValues[next - 1] + newValue;
            stackOldValues[next - 1] += oldValue;
            stackNewValues[next - 1] += newValue;
            stackItems[next - 1] |= stackItems[next - 1] + 1;
            if (next - 1 != 0 && stackItems[next - 2] == stackItems[next - 1]) {
                stackOldValues[next - 2] += stackOldValues[next - 1];
                stackNewValues[next - 2] += stackNewValues[next - 1];
                next--;
            }
        }
}

int32_t findFirstInterval3(tree_t const * const tree,
        int32_t const value,
        uint8_t(* const table)[256]) {
    assert(value >= 0);
    assert(value < getTotal3(tree));
    assert(isNonDecreasing3(tree, table));
    int32_t const items = tree->items;
    int32_t result = 0;
    int32_t sum = 0;
    int32_t interval = items - 1;
    while ((interval & interval - 1) > 0)
        interval &= interval - 1;
    while (interval > 0) {
        if (result + interval < items &&
                sum + tree->at[result + interval - 1] <= value) {
            sum += tree->at[result + interval - 1];
            result += interval;
        }
        interval >>= 1;
    }
    return result;
}

bool compare1(frequencies_t const * const frequencies,
        cumulative_t const * const cumulatives) {
    if (frequencies->items != cumulatives->items)
        return false;
    int32_t const items = frequencies->items;
    int32_t sum = 0;
    for (int32_t i = 0; i < items; i++) {
        sum += frequencies->at[i];
        if (sum != cumulatives->at[i])
            return false;
    }
    return true;
}

bool compare2(frequencies_t const * const frequencies,
        tree_t const * const tree,
        uint8_t(* const table)[256]) {
    if (frequencies->items != tree->items)
        return false;
    int32_t const items = frequencies->items;
    int32_t const ilog = computeLog(table, items);
    int32_t stackItems[ilog];
    int32_t stackValues[ilog];
    int32_t next = 0;
    for (int32_t i = 0; i < items; i++)
        if (i % 2 == 0) {
            if (frequencies->at[i] != tree->at[i])
                return false;
            if (next == 0 || stackItems[next - 1] != i + 1) {
                stackItems[next] = i + 1;
                stackValues[next] = frequencies->at[i];
                next++;
            } else
                stackValues[next - 1] += frequencies->at[i];
        } else {
            if (frequencies->at[i] + stackValues[next - 1] != tree->at[i])
                return false;
            stackValues[next - 1] += frequencies->at[i];
            stackItems[next - 1] |= stackItems[next - 1] + 1;
            if (next - 1 != 0 && stackItems[next - 2] == stackItems[next - 1]) {
                stackValues[next - 2] += stackValues[next - 1];
                next--;
            }
        }
    return true;
}

bool compare3(cumulative_t const * const cumulative,
        tree_t const * const tree,
        uint8_t(* const table)[256]) {
    if (cumulative->items != tree->items)
        return false;
    int32_t const items = cumulative->items;
    int32_t const ilog = computeLog(table, items);
    int32_t stackItems[ilog];
    int32_t stackValues[ilog];
    int32_t prevCumulative = 0;
    int32_t next = 0;
    for (int32_t i = 0; i < items; i++) {
        if (i % 2 == 0) {
            if (cumulative->at[i] - prevCumulative != tree->at[i])
                return false;
            if (next == 0 || stackItems[next - 1] != i + 1) {
                stackItems[next] = i + 1;
                stackValues[next] = cumulative->at[i] - prevCumulative;
                next++;
            } else
                stackValues[next - 1] += cumulative->at[i] - prevCumulative;
        } else {
            if (cumulative->at[i] - prevCumulative + stackValues[next - 1] !=
                    tree->at[i])
                return false;
            stackValues[next - 1] += cumulative->at[i] - prevCumulative;
            stackItems[next - 1] |= stackItems[next - 1] + 1;
            if (next - 1 != 0 && stackItems[next - 2] == stackItems[next - 1]) {
                stackValues[next - 2] += stackValues[next - 1];
                next--;
            }
        }
        prevCumulative = cumulative->at[i];
    }
    return true;
}

bool convertFrequenciesToCumulative(
        frequencies_t const * const frequencies,
        cumulative_t * const cumulative) {
    if (frequencies->items != cumulative->items)
        return false;
    int32_t sum = 0;
    for (int32_t i = 0; i < frequencies->items; i++) {
        sum += frequencies->at[i];
        cumulative->at[i] = sum;
    }
    return true;
}

bool convertFrequenciesToTree(
        frequencies_t const * const frequencies,
        tree_t * const tree,
        uint8_t(* const table)[256]) {
    if (frequencies->items != tree->items)
        return false;
    int32_t const items = frequencies->items;
    int32_t const ilog = computeLog(table, items);
    int32_t stackItems[ilog];
    int32_t stackValues[ilog];
    int32_t next = 0;
    for (int32_t i = 0; i < items; i++)
        if (i % 2 == 0) {
            tree->at[i] = frequencies->at[i];
            if (next == 0 || stackItems[next - 1] != i + 1) {
                stackItems[next] = i + 1;
                stackValues[next] = frequencies->at[i];
                next++;
            } else
                stackValues[next - 1] += frequencies->at[i];
        } else {
            int32_t const newValue = frequencies->at[i] + stackValues[next - 1];
            stackValues[next - 1] += frequencies->at[i];
            tree->at[i] = newValue;
            stackItems[next - 1] |= stackItems[next - 1] + 1;
            if (next - 1 != 0 && stackItems[next - 2] == stackItems[next - 1]) {
                stackValues[next - 2] += stackValues[next - 1];
                next--;
            }
        }
    return true;
}

bool convertCumulativeToFrequencies(
        cumulative_t const * const cumulative,
        frequencies_t * const frequencies) {
    if (frequencies->items != cumulative->items)
        return false;
    int32_t prev = 0;
    for (int32_t i = 0; i < cumulative->items; i++) {
        int32_t const current = cumulative->at[i];
        frequencies->at[i] = current - prev;
        prev = current;
    }
    return true;
}

bool convertCumulativeToTree(
        cumulative_t const * const cumulative,
        tree_t * const tree,
        uint8_t(* const table)[256]) {
    if (cumulative->items != tree->items)
        return false;
    int32_t const items = cumulative->items;
    int32_t const ilog = computeLog(table, items);
    int32_t stackItems[ilog];
    int32_t stackValues[ilog];
    int32_t prevCumulative = 0;
    int32_t next = 0;
    for (int32_t i = 0; i < items; i++) {
        if (i % 2 == 0) {
            int32_t const frequency = cumulative->at[i] - prevCumulative;
            prevCumulative = cumulative->at[i];
            tree->at[i] = frequency;
            if (next == 0 || stackItems[next - 1] != i + 1) {
                stackItems[next] = i + 1;
                stackValues[next] = frequency;
                next++;
            } else
                stackValues[next - 1] += frequency;
        } else {
            int32_t const frequency = cumulative->at[i] - prevCumulative;
            prevCumulative = cumulative->at[i];
            tree->at[i] = frequency + stackValues[next - 1];
            stackValues[next - 1] += frequency;
            stackItems[next - 1] |= stackItems[next - 1] + 1;
            if (next - 1 != 0 && stackItems[next - 2] == stackItems[next - 1]) {
                stackValues[next - 2] += stackValues[next - 1];
                next--;
            }
        }
    }
    return true;
}

bool convertTreeToFrequencies(
        tree_t const * const tree,
        frequencies_t * const frequencies,
        uint8_t(* const table)[256]) {
    if (tree->items != frequencies->items)
        return false;
    int32_t const items = tree->items;
    int32_t const ilog = computeLog(table, items);
    int32_t stackItems[ilog];
    int32_t stackValues[ilog];
    int32_t next = 0;
    for (int32_t i = 0; i < items; i++)
        if (i % 2 == 0) {
            frequencies->at[i] = tree->at[i];
            if (next == 0 || stackItems[next - 1] != i + 1) {
                stackItems[next] = i + 1;
                stackValues[next] = frequencies->at[i];
                next++;
            } else
                stackValues[next - 1] += frequencies->at[i];
        } else {
            frequencies->at[i] = tree->at[i] - stackValues[next - 1];
            stackValues[next - 1] += frequencies->at[i];
            stackItems[next - 1] |= stackItems[next - 1] + 1;
            if (next - 1 != 0 && stackItems[next - 2] == stackItems[next - 1]) {
                stackValues[next - 2] += stackValues[next - 1];
                next--;
            }
        }
    return true;
}

bool convertTreeToCumulative(
        tree_t const * const tree,
        cumulative_t * const cumulative,
        uint8_t(* const table)[256]) {
    if (tree->items != cumulative->items)
        return false;
    int32_t const items = tree->items;
    int32_t const ilog = computeLog(table, items);
    int32_t stackItems[ilog];
    int32_t stackValues[ilog];
    int32_t sum = 0;
    int32_t next = 0;
    for (int32_t i = 0; i < items; i++)
        if (i % 2 == 0) {
            int32_t const frequency = tree->at[i];
            sum += frequency;
            cumulative->at[i] = sum;
            if (next == 0 || stackItems[next - 1] != i + 1) {
                stackItems[next] = i + 1;
                stackValues[next] = frequency;
                next++;
            } else
                stackValues[next - 1] += frequency;
        } else {
            int32_t const frequency = tree->at[i] - stackValues[next - 1];
            sum += frequency;
            cumulative->at[i] = sum;
            stackValues[next - 1] += frequency;
            stackItems[next - 1] |= stackItems[next - 1] + 1;
            if (next - 1 != 0 && stackItems[next - 2] == stackItems[next - 1]) {
                stackValues[next - 2] += stackValues[next - 1];
                next--;
            }
        }
    return true;
}

int main(int argc, char const * * const argv) {
    uint8_t logTable[256];
    makeLogTable(logTable, 256);
    srand(0);
    for (int32_t length = 1; length < 1000; length++) {
        frequencies_t frequencies = makeFrequencies(length);
        cumulative_t cumulatives = makeCumulative(length);
        tree_t tree = makeTree(length);
        for (int32_t i = 0; i < 1000; i++) {
            int32_t const key = rand() % length;
            int32_t const value1 = rand() % 1000;
            assert(equal(
                    getFrequency1(&frequencies, key),
                    getFrequency2(&cumulatives, key),
                    getFrequency3(&tree, key)));
            adjustFrequency1(&frequencies, key, value1);
            adjustFrequency2(&cumulatives, key, value1);
            adjustFrequency3(&tree, key, value1);
            assert(equal(
                    getCumulativeInclusive1(&frequencies, key),
                    getCumulativeInclusive2(&cumulatives, key),
                    getCumulativeInclusive3(&tree, key)));
            int32_t const from = rand() % length;
            int32_t const to = from + rand() % (length - from);
            int32_t const value2 = rand() % 10;
            adjustRangeByValue1(&frequencies, from, to, value2);
            adjustRangeByValue2(&cumulatives, from, to, value2);
            adjustRangeByValue3(&tree, from, to, value2);
            assert(compare1(&frequencies, &cumulatives));
            assert(compare2(&frequencies, &tree, &logTable));
            assert(compare3(&cumulatives, &tree, &logTable));
            if (value1 < value2) {
                rescale1(&frequencies);
                rescale2(&cumulatives);
                rescale3(&tree, &logTable);
            }
            assert(equal(
                    getCumulativeExclusive1(&frequencies, key),
                    getCumulativeExclusive2(&cumulatives, key),
                    getCumulativeExclusive3(&tree, key)));
            assert(equal(
                    getTotal1(&frequencies),
                    getTotal2(&cumulatives),
                    getTotal3(&tree)));
            assert(isNonDecreasing1(&frequencies) ==
                    isNonDecreasing2(&cumulatives));
            assert(isNonDecreasing2(&cumulatives) ==
                    isNonDecreasing3(&tree, &logTable));
            int32_t const toFind = rand() % getTotal2(&cumulatives);
            assert(findFirstInterval1(&frequencies, toFind) ==
                    findFirstInterval2(&cumulatives, toFind));
            assert(findFirstInterval2(&cumulatives, toFind) ==
                    findFirstInterval3(&tree, toFind, &logTable));
            switch (rand() % 100) {
                case 0:
                    assert(convertFrequenciesToCumulative(&frequencies,
                            &cumulatives));
                    break;
                case 1:
                    assert(convertFrequenciesToTree(&frequencies,
                            &tree, &logTable));
                    break;
                case 2:
                    assert(convertCumulativeToFrequencies(&cumulatives,
                            &frequencies));
                    break;
                case 3:
                    assert(convertCumulativeToTree(&cumulatives,
                            &tree, &logTable));
                    break;
                case 4:
                    assert(convertTreeToFrequencies(&tree,
                            &frequencies, &logTable));
                    break;
                case 5:
                    assert(convertTreeToCumulative(&tree,
                            &cumulatives, &logTable));
                    break;
                case 6:
                {
                    cumulative_t fakeCumulatives;
                    fakeCumulatives.items = frequencies.items;
                    fakeCumulatives.at = frequencies.at;
                    tree_t fakeTree;
                    fakeTree.items = frequencies.items;
                    fakeTree.at = frequencies.at;
                    assert(convertFrequenciesToCumulative(&frequencies,
                            &fakeCumulatives));
                    assert(convertCumulativeToTree(&fakeCumulatives,
                            &fakeTree, &logTable));
                    assert(convertTreeToFrequencies(&fakeTree,
                            &frequencies, &logTable));
                }
                    break;
                case 7:
                {
                    tree_t fakeTree;
                    fakeTree.items = frequencies.items;
                    fakeTree.at = frequencies.at;
                    cumulative_t fakeCumulatives;
                    fakeCumulatives.items = frequencies.items;
                    fakeCumulatives.at = frequencies.at;
                    assert(convertFrequenciesToTree(&frequencies,
                            &fakeTree, &logTable));
                    assert(convertTreeToCumulative(&fakeTree,
                            &fakeCumulatives, &logTable));
                    assert(convertCumulativeToFrequencies(&fakeCumulatives,
                            &frequencies));
                }
                    break;
            }
        }
    }
    puts("Assertions passed.");
    return EXIT_SUCCESS;
}
/*
        Last edited by Piotr Tarsa; 30th December 2011 at 03:01. 

    Reply With Quote Reply With Quote
    30th December 2011, 03:11 #2
    Piotr Tarsa
    Piotr Tarsa is offline
    Member

    Join Date
        Jun 2009
    Location
        Cracov, Poland
    Posts
        605

        I've added several new functions. Now there are functions for:
        - adjusting single item,
        - adjusting a consecutive range of items by same value,
        - comparing two structures with different representation,
        - converting from one representation to another - you can even convert in-place if you provide the same array pointer as the source and as the destination,
        - finding first interval in which a provided value lies (useful eg in decoding),
        - computing cumulative (inclusive and exclusive) values of items,
        - computing values of items,
        - computing sum of all items,
        - rescaling,

        All functions have versions for each representation and their complexities are either constant, logarithmic or linear. 

        Last edited by Piotr Tarsa; 30th December 2011 at 03:15. 

    Reply With Quote Reply With Quote
    30th December 2011, 04:32 #3
    Shelwien
    Shelwien is online now
    Administrator Shelwien's Avatar

    Join Date
        May 2008
    Location
        Kharkov, Ukraine
    Posts
        1,773

        Can you explain in which cases this is actually helpful?
        I've seen something similar in cbloom's blog, but even then I didn't understand the point of it.
        Its not any better than binary search, nor it saves any memory, afair.
        So what kind of coder would benefit from that?

        Also, why do you post this stuff (this and SR vs PPM thread too) in offtopic, how about moving it to "data compression"? 

    Reply With Quote Reply With Quote
    30th December 2011, 05:13 #4
    Piotr Tarsa
    Piotr Tarsa is offline
    Member

    Join Date
        Jun 2009
    Location
        Cracov, Poland
    Posts
        605

        I wasn't 100 % sure about the category. You can move those threads if you think it's appropriate.

        Not any better than binary search? Well, I've implemented binary search in above code also, for the cumulative_t data type, but that doesn't solve all problems.

        My tree structure provides:
        - adjusting single item value in O(lg n) time,
        - retrieving single item value in O(lg n) time,
        - retrieving the cumulative value of an item == sum of a prefix of a table in O(lg n) time,
        - rescaling whole tree in Theta(n) time using Theta(lg n) additional memory,
        - finding item with given cumulative value in O(lg n) time,

        Additionally, converting between all three representations takes always Theta(n) time and Theta(lg n) additional memory (but only when tree is involved, if not then the additional memory has constant size).

        Do you know non tree based structure that has at least the same computational complexities? Can you point me to that cbloom post about his solution?


        This data structure would be helpful eg in implementing arithmetic coded LZW or LZAP. Every entry can have a hit counter and be coded with (entry hits/ total hits) probability in logarithmic time using my data structure. Probably it could be even helpful with normal 256-symbols alphabet coding, maybe I'll write TarsaLZP version with that data structure soon. 

        Last edited by Piotr Tarsa; 30th December 2011 at 05:18. 

    Reply With Quote Reply With Quote
    30th December 2011, 07:38 #5
    Shelwien
    Shelwien is online now
    Administrator Shelwien's Avatar

    Join Date
        May 2008
    Location
        Kharkov, Ukraine
    Posts
        1,773

        > Do you know non tree based structure that has at least the same computational complexities?

        Tree-based is okay, its the i&(i-1) (and especially your i&(i+1)) stuff that confuses me.
        (I know what they do, just don't get why).
        Afaik, we only need a simple binary tree, like the one in bitwise CMs, where each node
        contains the sum of freqs in one of branches.
        Something like this:

        Code:

        for( i=7; i>=0; i-- ) {
          bit = (c>>i)&1;
          low += tree[ctx].low & (-bit);
          ctx+=ctx + bit;
        }

        > Can you point me to that cbloom post about his solution?

        There're at least two posts:
        http://cbloomrants.blogspot.com/2010...ity-trees.html
        http://cbloomrants.blogspot.com/2010...umulative.html 

    Reply With Quote Reply With Quote
    30th December 2011, 14:08 #6
    Sebastian
    Sebastian is offline
    Member

    Join Date
        Oct 2010
    Location
        Germany
    Posts
        183

        Afaik the original algorithm for this is from Peter Fenwick. 

    Reply With Quote Reply With Quote
    30th December 2011, 15:12 #7
    Fallon
    Fallon is offline
    Member Fallon's Avatar

    Join Date
        May 2008
    Location
        Europe - The Netherlands
    Posts
        101

        cbloom rants 2010-08-11 links to this little tutorial on Fenwick Trees:
        http://community.topcoder.com/tc?mod...ryIndexedTrees 

    Reply With Quote Reply With Quote
    30th December 2011, 16:55 #8
    Cyan
    Cyan is offline
    Member

    Join Date
        Sep 2008
    Location
        France
    Posts
        359

        Well, same comment. This is Fenwick Tree.
        It's fairly quick and efficient, and certainly more space-efficient than a tree (no pointer to store).

        However, in past tests, it was not "fast" enough for my needs.
        An update or reading of any value still costs log(n) access. 

    Reply With Quote Reply With Quote
    30th December 2011, 21:53 #9
    Matt Mahoney
    Matt Mahoney is offline
    Expert
    Matt Mahoney's Avatar

    Join Date
        May 2008
    Location
        Melbourne, Florida, USA
    Posts
        1,108

        Same as bitwise modeling. 

    Reply With Quote Reply With Quote
    30th December 2011, 22:29 #10
    Piotr Tarsa
    Piotr Tarsa is offline
    Member

    Join Date
        Jun 2009
    Location
        Cracov, Poland
    Posts
        605

        Duh, it seems I was late... Well, Fenwick discovered that when I was in a single digit age, so that isn't a shame I think.

        It's very similar to those bitwise modelling but not exactly the same. With bitwise modelling you either store single probability per context (thus losing the exact quantities) or you store a pair of counters (thus doubling memory usage). The main difference is in addressing.

        I think that with the Binary Indexed Trees, searching & updating & retrieving probability can be done in one pass. I'll try to implement that in my next version of TarsaLZP. 

    Reply With Quote Reply With Quote
    30th December 2011, 22:44 #11
    Shelwien
    Shelwien is online now
    Administrator Shelwien's Avatar

    Join Date
        May 2008
    Location
        Kharkov, Ukraine
    Posts
        1,773

        Answering my own question, the topcoder article kinda explains that the Fenwick tree is
        efficient when we need to compute sums of various x..y ranges.
        However, I usually prefer to do that via Sum(x..y) = Sum(0..y)-Sum(0..x) with a binary tree,
        its the same log2(N) anyway. And for compression we mostly need only Sum(0..x) anyway.
        Also afaiu the Fenwick tree doesn't take into account the cache line clustering
        (while its known how to take care of that with plain binary trees).

        Still, tricky structures are always interesting, even if useless 

    Reply With Quote Reply With Quote
    30th December 2011, 23:01 #12
    Sebastian
    Sebastian is offline
    Member

    Join Date
        Oct 2010
    Location
        Germany
    Posts
        183

        Quote Originally Posted by Shelwien View Post
        tricky structures are always interesting, even if useless

    Reply With Quote Reply With Quote
    31st December 2011, 01:27 #13
    Matt Mahoney
    Matt Mahoney is offline
    Expert
    Matt Mahoney's Avatar

    Join Date
        May 2008
    Location
        Melbourne, Florida, USA
    Posts
        1,108

        The disadvantage of bitwise modeling is that you have to call the arithmetic coder 8 times per byte, and when decompressing there is a serial dependency between predicting and updating (making it slower than compression). 

    Reply With Quote Reply With Quote
    31st December 2011, 01:28 #14
    Piotr Tarsa
    Piotr Tarsa is offline
    Member

    Join Date
        Jun 2009
    Location
        Cracov, Poland
    Posts
        605

        Fenwick tree *IS* a binary tree, just nodes that are left (or right, depending on algorithm details) childs are absent, because they can be easily recomputed.

        Also afaiu the Fenwick tree doesn't take into account the cache line clustering
        (while its known how to take care of that with plain binary trees).
        How?

        So, a little off-topic: What is your preferred approach to bytewise coding symbols from 256-byte alphabet, assuming we have allocated enough memory to address statistics about every context directly? I've tried two-level statistics in assembly version of TarsaLZP, where I sped up computations using MMX. First level has 16 slots, each for storing sum of 16 consecutive symbols. And it's rather fast. 

    Reply With Quote Reply With Quote
    31st December 2011, 01:36 #15
    Matt Mahoney
    Matt Mahoney is offline
    Expert
    Matt Mahoney's Avatar

    Join Date
        May 2008
    Location
        Melbourne, Florida, USA
    Posts
        1,108

        Personally I prefer bitwise modeling (CM) because you have so much more flexibility in computing predictions. But like I said it is probably slower, even if the complexity is theoretically the same. Sadly, PPM is the only type of compressor I haven't written, out of most of the major algorithms, so maybe I'm biased. 

    Reply With Quote Reply With Quote
    31st December 2011, 02:02 #16
    Shelwien
    Shelwien is online now
    Administrator Shelwien's Avatar

    Join Date
        May 2008
    Location
        Kharkov, Ukraine
    Posts
        1,773

        > How?

        Why, split it into smaller trees which would fit to cache lines.

        > So, a little off-topic: What is your preferred approach to bytewise
        > coding symbols from 256-byte alphabet, assuming we have allocated
        > enough memory to address statistics about every context directly?

        Well, usually looking up the statistics is the main point though.
        Like, you can't really store cumulative freqs in a PPM tree,
        because you won't be able to store cumulative freqs as bytes.

        > I've tried two-level statistics in assembly version of TarsaLZP,
        > where I sped up computations using MMX. First level has 16 slots,
        > each for storing sum of 16 consecutive symbols. And it's rather fast.

        Yeah, these days linear scanning is frequently better than any
        smart indexing.
        But I don't see any potential for freq-based models anymore.
        (aside from bytewise coding which can be used with bitwise models too;
        basically a bytewise rc is a rc which is only normalized between symbols)
        With huffman decomposition etc the bitwise CM would be as fast as freq-based bytewise,
        but would be also stronger (especially on binaries) and there're lots of
        known improvements to apply (like fsm counters and parallel rc).

        I guess the only unbeatable design would be the static bytewise coder,
        as it doesn't need divisions, but on other hand, in that case there won't
        be any freqs already anyway.

        However, I still think that trees are more interesting than hashtables.
        Imho the main reason why ppmd is faster than ccm is not the freq-based model,
        but the tree. 

    Reply With Quote Reply With Quote
    31st December 2011, 03:07 #17
    Shelwien
    Shelwien is online now
    Administrator Shelwien's Avatar

    Join Date
        May 2008
    Location
        Kharkov, Ukraine
    Posts
        1,773

        > Personally I prefer bitwise modeling (CM) because you have so much
        > more flexibility in computing predictions.

        Imho CM is not a matter of preference at all.
        There're some alternatives (eg. data transformations),
        but CM is the only approach with known mathematical foundations,
        and also sequential and easily tunable.

        As to bitwise modelling, it has a few drawbacks
        (eg. alphabet reordering, especially for texts;
        precision issues with non-power-of-2 alphabets),
        but working with bits is usually the simplest,
        so there's no way around it in the end - eg.
        its possible to implement SSE or logistic mixing
        for n-ary alphabets, but they would be both
        much more complex and less precise.

        > But like I said it is probably slower, even if the complexity is
        > theoretically the same.

        Its not really slower. ccm speed is 3-5Mb/s depending on model size
        and ppmd speed is 1-9Mb/s depending on redundancy of data
        (its faster for more compressible data).
        And there're also ways to make a faster bitwise CM, though
        unfortunately they're not quite incremental - ie we need
        to build a new CM from scratch for it to be really better.

        > Sadly, PPM is the only type of compressor I haven't written,
        > out of most of the major algorithms, so maybe I'm biased.

        Imho there's no point in writing a new PPM based on the same ideas -
        it would be slow with hashtable, and it would be very similar to PPMd
        with a tree - the largest part of PPM is about accessing the stats,
        escaping to lower orders, masking the symbols, and coding.
        So I think that any new PPM with a tree and byte freqs would end up
        very similar to ppmd.

        I don't mean that there's no sense to write a new PPM though - just
        suggesting to use a different design.
        Like make a PPM/LZ77 hybrid with optimal parsing, or PPM with fsm counters,
        or invent a better data structure than ppmd's suffix tree. 

    Reply With Quote Reply With Quote
*/
