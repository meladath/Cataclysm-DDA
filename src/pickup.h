#pragma once
#ifndef CATA_SRC_PICKUP_H
#define CATA_SRC_PICKUP_H

#include <vector>
#include "point.h"
#include "ui.h"

class item;
class item_location;
class Character;
class map;
struct tripoint;

namespace Pickup
{
/**
 * Returns `false` if the player was presented a prompt and decided to cancel the pickup.
 * `true` in other cases.
 */
bool do_pickup( std::vector<item_location> &targets, std::vector<int> &quantities,
                bool autopickup );
bool query_thief();

enum from_where : int {
    from_cargo = 0,
    from_ground,
    prompt
};

/** Pick up items; 'g' or ',' or via examine() */
void pick_up( const tripoint &p, int min, from_where get_items_from = prompt );
/** Determines the cost of moving an item by a character. */
int cost_to_move_item( const Character &who, const item &it );

/**
 * If character is handling a potentially spillable bucket, gracefully handle what
 * to do with the contents.
 *
 * Returns true if we handled the container, false if we chose to spill the
 * contents and the container still needs to be put somewhere.
 * @param c Character handling the spillable item
 * @param it item to handle
 * @param m map they are on
 */
bool handle_spillable_contents( Character &c, item &it, map &m );

struct pickup_rect : inclusive_rectangle<point> {
    pickup_rect() = default;
    pickup_rect( const point &P_MIN, const point &P_MAX ) : inclusive_rectangle( P_MIN, P_MAX ) {}
    int cur_it;
    static std::vector<pickup_rect> list;
    static pickup_rect *find_by_coordinate( const point &p );
};

} // namespace Pickup
#endif // CATA_SRC_PICKUP_H
