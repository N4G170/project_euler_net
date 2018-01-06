#ifndef ENUMS_HPP
#define ENUMS_HPP

enum TextAlignment
{
    TOP_LEFT = 0,
    CENTER = 1,
    TOP_RIGHT = 2
};

enum Weekdays//for problems
{
    SUNDAY,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
};

enum Months//for problems
{
    JANUARY,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
};

enum TimeScale
{
    SECONDS,
    MILLISECONDS
};

enum FontRenderType
{
    SOLID,
    SHADED,
    BLENDED
};

enum ResourceManagerContext
{
    NONE,
    SPLASH,
    PROBLEMS
};

/**
 * \brief this enum is tmp
 */
enum FontSizes
{
    S_12 = 12,
    S_20 = 20,
    S_28 = 28
};
#endif
