 

  
pragma solidity ^0.4.0;

 contract LuckyDoubler {
 
 
 
 
 
 
 
 

    address private owner;

     
    uint private balance = 0;
    uint private fee = 5;
    uint private multiplier = 125;

    mapping (address => User) private users;
    Entry[] private entries;
    uint[] private unpaidEntries;

     
    function LuckyDoubler() {
        owner = msg.sender;
    }

    modifier onlyowner { if (msg.sender == owner) _; }

    struct User {
        address id;
        uint deposits;
        uint payoutsReceived;
    }

    struct Entry {
        address entryAddress;
        uint deposit;
        uint payout;
        bool paid;
    }

     
    function() {
        init();
    }

    function init() private{

        if (msg.value < 1 ether) {
             msg.sender.send(msg.value);
            return;
        }

        join();
    }

    function join() private {

         
        uint dValue = 1 ether;

        if (msg.value > 1 ether) {

        	msg.sender.send(msg.value - 1 ether);
        	dValue = 1 ether;
        }

         
        if (users[msg.sender].id == address(0))
        {
            users[msg.sender].id = msg.sender;
            users[msg.sender].deposits = 0;
            users[msg.sender].payoutsReceived = 0;
        }

         
        entries.push(Entry(msg.sender, dValue, (dValue * (multiplier) / 100), false));
        users[msg.sender].deposits++;
        unpaidEntries.push(entries.length -1);

         
        balance += (dValue * (100 - fee)) / 100;

        uint index = unpaidEntries.length > 1 ? rand(unpaidEntries.length) : 0;
        Entry theEntry = entries[unpaidEntries[index]];

         
        if (balance > theEntry.payout) {

            uint payout = theEntry.payout;

            theEntry.entryAddress.send(payout);
            theEntry.paid = true;
            users[theEntry.entryAddress].payoutsReceived++;

            balance -= payout;

            if (index < unpaidEntries.length - 1)
                unpaidEntries[index] = unpaidEntries[unpaidEntries.length - 1];

            unpaidEntries.length--;

        }

         
        uint fees = this.balance - balance;
        if (fees > 0)
        {
                owner.send(fees);
        }

    }

     
    uint256 constant private FACTOR =  1157920892373161954235709850086879078532699846656405640394575840079131296399;
     
    function rand(uint max) constant private returns (uint256 result){
        uint256 factor = FACTOR * 100 / max;
        uint256 lastBlockNumber = block.number - 1;
        uint256 hashVal = uint256(block.blockhash(lastBlockNumber));

        return uint256((uint256(hashVal) / factor)) % max;
    }


     
    function changeOwner(address newOwner) onlyowner {
        owner = newOwner;
    }

    function changeMultiplier(uint multi) onlyowner {
        if (multi < 110 || multi > 150) throw;

        multiplier = multi;
    }

    function changeFee(uint newFee) onlyowner {
        if (fee > 5)
            throw;
        fee = newFee;
    }


     
    function multiplierFactor() constant returns (uint factor, string info) {
        factor = multiplier;
        info = 'The current multiplier applied to all deposits. Min 110%, max 150%.';
    }

    function currentFee() constant returns (uint feePercentage, string info) {
        feePercentage = fee;
        info = 'The fee percentage applied to all deposits. It can change to speed payouts (max 5%).';
    }

    function totalEntries() constant returns (uint count, string info) {
        count = entries.length;
        info = 'The number of deposits.';
    }

    function userStats(address user) constant returns (uint deposits, uint payouts, string info)
    {
        if (users[user].id != address(0x0))
        {
            deposits = users[user].deposits;
            payouts = users[user].payoutsReceived;
            info = 'Users stats: total deposits, payouts received.';
        }
    }

    function entryDetails(uint index) constant returns (address user, uint payout, bool paid, string info)
    {
        if (index < entries.length) {
            user = entries[index].entryAddress;
            payout = entries[index].payout / 1 finney;
            paid = entries[index].paid;
            info = 'Entry info: user address, expected payout in Finneys, payout status.';
        }
    }


}

contract Auction {
  
  uint public price;
  uint public timestampEnd;
  address public beneficiary;
  bool public initialPrice = true;
  address public winner;
  mapping(address => uint) public bids;
  address[] public accountsList;
  uint public increaseTimeIfBidBeforeEnd = 24 * 60 * 60;
  uint public increaseTimeBy = 24 * 60 * 60;
  
  event BidEvent(address indexed bidder, uint value, uint timestamp);

  function bid() public payable {
    require(now < timestampEnd, "auction has ended");

    if (bids[msg.sender] > 0) {
      bids[msg.sender] += msg.value;
    } else {
      bids[msg.sender] = msg.value;
      accountsList.push(msg.sender);
    }

    if (initialPrice) {
      require(bids[msg.sender] >= price, "bid too low, minimum is the initial price");
    } else {
      require(bids[msg.sender] >= (price * 5 / 4), "bid too low, minimum 25% increment");
    }
    
    if (now > timestampEnd - increaseTimeIfBidBeforeEnd) {
      timestampEnd = now + increaseTimeBy;
    }

    initialPrice = false;
    price = bids[msg.sender];
    winner = msg.sender;
    emit BidEvent(winner, msg.value, now);
  }
}

contract AuctionMultiple is Auction {

  uint public constant LIMIT = 2000;
  uint public constant HEAD = 120000000 * 1e18;
  uint public constant TAIL = 0;
  uint public lastBidID = 0;
  uint public howMany;

  struct Bid {
    uint prev;
    uint next;
    uint value;
    address contributor;
  }    

  mapping (uint => Bid) public bids;
  mapping (address => uint) public contributors;

  function bid() public payable {
    require(now < timestampEnd, "cannot bid after the auction ends");

    uint myBidId = contributors[msg.sender];
    uint insertionBidId;
    
    if (myBidId > 0) {
      Bid storage existingBid = bids[myBidId];
      existingBid.value = existingBid.value + msg.value;
      if (existingBid.value > bids[existingBid.next].value) {
        insertionBidId = searchInsertionPoint(existingBid.value, existingBid.next);

        bids[existingBid.prev].next = existingBid.next;
        bids[existingBid.next].prev = existingBid.prev;

        existingBid.prev = insertionBidId;
        existingBid.next = bids[insertionBidId].next;

        bids[ bids[insertionBidId].next ].prev = myBidId;
        bids[insertionBidId].next = myBidId;
      } 

    } else {
      require(msg.value >= price, "Not much sense sending less than the price, likely an error");
      require(lastBidID < LIMIT, "Due to blockGas limit we limit number of people in the auction to 4000");

      lastBidID++;

      insertionBidId = searchInsertionPoint(msg.value, TAIL);

      contributors[msg.sender] = lastBidID;
      accountsList.push(msg.sender);

      bids[lastBidID] = Bid({
        prev: insertionBidId,
        next: bids[insertionBidId].next,
        value: msg.value,
        contributor: msg.sender
      });

      bids[ bids[insertionBidId].next ].prev = lastBidID;
      bids[insertionBidId].next = lastBidID;
    }

    emit BidEvent(msg.sender, msg.value, now);
  }

  function searchInsertionPoint(uint _contribution, uint _startSearch) view public returns (uint) {
    require(_contribution > bids[_startSearch].value, "your contribution and _startSearch does not make sense");

    Bid memory lowerBid = bids[_startSearch];
    Bid memory higherBid;

    while(true) {
      higherBid = bids[lowerBid.next];

      if (_contribution < higherBid.value) {
        return higherBid.prev;
      } else {
        lowerBid = higherBid;
      }
    }
  }
}
