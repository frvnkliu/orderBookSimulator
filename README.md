## Order Book Simulator
Simulates an Order Book for a single Stock. Prints the actions/results of each trade, as well as the final state of the order book at the end of input.
* Created using 2 Priority Queues
* A self defined `Trade` struct
* 2 Custom Comparator Functions

#### Input Format:
* One line with a single number - `n`, represents the number of trades
* Followed by `n` lines of trades in the following format: `p q b t`
  * `p` - Price of the trade (Represented by int)
  * `q` - Quantity of the trade (Represented by int)
  * `b` - Character representing direction of trade: `b` = "b", means buy, sell otherwise (Represented by char)
  * `t` - Time of trade (Represented by int)




