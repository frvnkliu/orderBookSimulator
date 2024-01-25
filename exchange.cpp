#include <queue>
#include <iostream>
#include <iomanip>

using namespace std;

struct Trade {
	int price; //in cents
    int quantity;
	bool buy;
	int time;

    // Constructor for convenience
    Trade(int p, int q, bool b, int t) : price(p), quantity(q), buy(b), time(t) {}
};

//Price-Time Priority 
struct PTPriorityComparator{ 
	bool operator()(const Trade& a, const Trade& b) const {
        return (a.buy ? a.price <  b.price : a.price > b.price) || a.time > b.time; // Assumes a.buy == b.buy
	}
};

struct TimeComparator {
    bool operator()(const Trade& a, const Trade& b) const {
        return a.time < b.time;
    }
};

int main() {
    //Parse input
	int n, p, q, t;
	char c;
	vector<Trade> trades; 
	scanf("%d", &n);
	for(int i = 0; i<n; i++){	
		scanf("%d %d %c %d", &p, &q, &c, &t);
		Trade trade(p,q, c=='b',t);
		trades.push_back(trade);
	}
	
	sort(trades.begin(), trades.end(), TimeComparator());

	priority_queue<Trade, vector<Trade>, PTPriorityComparator> bids;
	priority_queue<Trade, vector<Trade>, PTPriorityComparator> offers;

	for(Trade trade: trades){
		//see if it is bid or offer
		cout << "Current Trade: " << endl;
		cout << "-- price: " << trade.price <<endl;
		cout << "-- quantity: " << trade.quantity <<endl;
		cout << "-- buy: " << trade.buy <<endl;
		cout << "-- time: " << trade.time <<endl;
		
		int initial = trade.quantity;
		//first check if there are any crosses
		if(trade.buy){ //Buying
			while(trade.quantity && !offers.empty() && offers.top().price <= trade.price){
				if(offers.top().quantity > trade.quantity){
					Trade& offer = const_cast<Trade&>(offers.top());
					offer.quantity -= trade.quantity;
					trade.quantity = 0;
					cout << " === " << trade.quantity << " shares, bought at  " << offer.price << endl; 
				}else{
					trade.quantity -= offers.top().quantity;
					cout << " === " << offers.top().quantity << " shares, bought at  " << offers.top().price << endl; 
					offers.pop();
				}
			}
		}else{ //Selling
			while(trade.quantity && !bids.empty() && bids.top().price >= trade.price){
				if(bids.top().quantity > trade.quantity){
					Trade& bid = const_cast<Trade&>(bids.top());
					bid.quantity -= trade.quantity;
					trade.quantity = 0;
					cout << "  == " << bids.top().quantity << " shares, sold at  " << bid.price << endl; 
				}else{
					trade.quantity -= bids.top().quantity;
					cout << "  == " << bids.top().quantity << " shares, bought at  " << bids.top().price << endl; 
					bids.pop();
				}
			}
		}
		//Check if there is leftover
		if(trade.quantity){
			if(trade.quantity-initial) cout << "  Partial Execution: " << trade.quantity << " shares remaining" << endl;
			else cout << "  Trade Unexecuted" << endl;
			
			if(trade.buy) bids.push(trade);
			else offers.push(trade);
		}else{
			cout << "  Trade Fully Executed" << endl;
		}
	}
	
	//Print final Queues
	const int columnWidth = 17;
	cout << "===Final Order Book===" << endl;
	// Print column labels
    cout << "| " << setw(columnWidth) << "Bid Quantity";
    cout << " | "<< setw(columnWidth) << "Bid Price";
    cout << " | " << setw(columnWidth) << "Ask Price";
    cout << " | " << setw(columnWidth) << "Ask Quantity";
	cout << " |" << endl;

    while (!bids.empty() || !offers.empty()) {
        // Print bid information if available
        if (!bids.empty()) {
            Trade bid = bids.top();
            bids.pop();
            cout << "| "<< setw(columnWidth) << bid.quantity;
            cout <<  " | " << setw(columnWidth) << bid.price;
        } else {
            cout << "| " << setw(columnWidth) << " ";
            cout << " | " << setw(columnWidth) << " ";
        }

        // Print offer information if available
        if (!offers.empty()) {
            Trade offer = offers.top();
            offers.pop();
            cout << " | "<< setw(columnWidth) << offer.price;
            cout <<  " | " << setw(columnWidth) << offer.quantity;
        } else {
            cout << " | " << setw(columnWidth) << " ";
            cout << " | " << setw(columnWidth) << " ";
        }
        cout << " |" << endl;
    }
    return 0;
}
