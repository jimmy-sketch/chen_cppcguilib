#pragma once

struct logicPos {
    int row, col;
};
static bool operator<(logicPos lhs, logicPos rhs) {
    return (lhs.row < rhs.row) || (lhs.row == rhs.row && lhs.col < rhs.col);
}
static bool operator==(logicPos lhs, logicPos rhs) {
    return (lhs.row == rhs.row) && (lhs.col == rhs.col);
}