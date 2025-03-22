 

 
pragma solidity ^0.4.0;

 contract Lotto {

     uint constant public blocksPerRound = 6800;
      

     uint constant public ticketPrice = 100000000000000000;
      

     uint constant public blockReward = 5000000000000000000;

     function getBlocksPerRound() constant returns(uint){ return blocksPerRound; }
     function getTicketPrice() constant returns(uint){ return ticketPrice; }
      

     struct Round {
         address[] buyers;
         uint pot;
         uint ticketsCount;
         mapping(uint=>bool) isCashed;
         mapping(address=>uint) ticketsCountByBuyer;
     }
     mapping(uint => Round) rounds;
      

     function getRoundIndex() constant returns (uint){
          

         return block.number/blocksPerRound;
     }

     function getIsCashed(uint roundIndex,uint subpotIndex) constant returns (bool){
          

         return rounds[roundIndex].isCashed[subpotIndex];
     }


     function calculateWinner(uint roundIndex, uint subpotIndex) constant returns(address){
          

         var decisionBlockNumber = getDecisionBlockNumber(roundIndex,subpotIndex);

         if(decisionBlockNumber>block.number)
             return;
          

         var decisionBlockHash = getHashOfBlock(decisionBlockNumber);
         var winningTicketIndex = decisionBlockHash%rounds[roundIndex].ticketsCount;
          

         var ticketIndex = uint256(0);

         for(var buyerIndex = 0; buyerIndex<rounds[roundIndex].buyers.length; buyerIndex++){
             var buyer = rounds[roundIndex].buyers[buyerIndex];
             ticketIndex+=rounds[roundIndex].ticketsCountByBuyer[buyer];

             if(ticketIndex>winningTicketIndex){
                 return buyer;
             }
         }
     }

     function getDecisionBlockNumber(uint roundIndex,uint subpotIndex) constant returns (uint){
         return ((roundIndex+1)*blocksPerRound)+subpotIndex;
     }

     function getSubpotsCount(uint roundIndex) constant returns(uint){
         var subpotsCount = rounds[roundIndex].pot/blockReward;

         if(rounds[roundIndex].pot%blockReward>0)
             subpotsCount++;

         return subpotsCount;
     }

     function getSubpot(uint roundIndex) constant returns(uint){
         return rounds[roundIndex].pot/getSubpotsCount(roundIndex);
     }

     function cash(uint roundIndex, uint subpotIndex){

         var subpotsCount = getSubpotsCount(roundIndex);

         if(subpotIndex>=subpotsCount)
             return;

         var decisionBlockNumber = getDecisionBlockNumber(roundIndex,subpotIndex);

         if(decisionBlockNumber>block.number)
             return;

         if(rounds[roundIndex].isCashed[subpotIndex])
             return;
          

         var winner = calculateWinner(roundIndex,subpotIndex);
         var subpot = getSubpot(roundIndex);

          
         winner.send(subpot);

         rounds[roundIndex].isCashed[subpotIndex] = true;
          
     }

     function getHashOfBlock(uint blockIndex) constant returns(uint){
         return uint(block.blockhash(blockIndex));
     }

     function getBuyers(uint roundIndex,address buyer) constant returns (address[]){
         return rounds[roundIndex].buyers;
     }

     function getTicketsCountByBuyer(uint roundIndex,address buyer) constant returns (uint){
         return rounds[roundIndex].ticketsCountByBuyer[buyer];
     }

     function getPot(uint roundIndex) constant returns(uint){
         return rounds[roundIndex].pot;
     }

     function() {
          

         var roundIndex = getRoundIndex();
         var value = msg.value-(msg.value%ticketPrice);

         if(value==0) return;

         if(value<msg.value){
              
             msg.sender.send(msg.value-value);
         }
          

         var ticketsCount = value/ticketPrice;
         rounds[roundIndex].ticketsCount+=ticketsCount;

         if(rounds[roundIndex].ticketsCountByBuyer[msg.sender]==0){
             var buyersLength = rounds[roundIndex].buyers.length++;
             rounds[roundIndex].buyers[buyersLength] = msg.sender;
         }

         rounds[roundIndex].ticketsCountByBuyer[msg.sender]+=ticketsCount;
         rounds[roundIndex].ticketsCount+=ticketsCount;
          

         rounds[roundIndex].pot+=value;
          

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
