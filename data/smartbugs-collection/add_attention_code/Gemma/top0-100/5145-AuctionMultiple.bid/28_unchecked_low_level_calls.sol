 

pragma solidity ^0.4.23;        

 
 
 
 
 
 
 
 
 
 
 
 
   
contract Delta {     

	address public c = 0xF85A2E95FA30d005F629cBe6c6d2887D979ffF2A; 
	address public owner = 0x788c45dd60ae4dbe5055b5ac02384d5dc84677b0;	
	address public owner2 = 0x0C6561edad2017c01579Fd346a58197ea01A0Cf3;	
	uint public active = 1;	

	uint public token_price = 10**18*1/1000; 	

	 
	function() payable {        
	    tokens_buy();        
	}

	 
    function tokens_buy() payable returns (bool) {         
        
        require(active > 0);
        require(msg.value >= token_price);        

        uint tokens_buy = msg.value*10**18/token_price;

        require(tokens_buy > 0);

        if(!c.call(bytes4(sha3("transferFrom(address,address,uint256)")),owner, msg.sender,tokens_buy)){
        	return false;
        }

        uint sum2 = msg.value * 3 / 10;           
         
        owner2.send(sum2);

        return true;
      }     

       
      function withdraw(uint256 _amount) onlyOwner returns (bool result) {
          uint256 balance;
          balance = this.balance;
          if(_amount > 0) balance = _amount;
           
          owner.send(balance);
          return true;
      }

       
      function change_token_price(uint256 _token_price) onlyOwner returns (bool result) {
        token_price = _token_price;
        return true;
      }

       
      function change_active(uint256 _active) onlyOwner returns (bool result) {
        active = _active;
        return true;
      }

       
    	modifier onlyOwner() {
        if (msg.sender != owner) {
            throw;
        }
        _;
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
