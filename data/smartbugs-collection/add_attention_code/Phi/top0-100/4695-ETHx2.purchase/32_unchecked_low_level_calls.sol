 

 
pragma solidity ^0.4.0;

 contract Lotto {

     uint constant public blocksPerRound = 6800;
      

     uint constant public ticketPrice = 100000000000000000;
      

     uint constant public blockReward = 5000000000000000000;



struct Cost {
    address owner;
    uint256 cost;
}

mapping(uint256 => Cost) public participant;

address public adminAddress;
uint256 public seatPrice = 5000000000000000;

function purchase() public payable {
    require(msg.sender != address(0));
    require(msg.value >= seatPrice);
    uint256 excess = SafeMath.sub(msg.value, seatPrice);
    participant[1].owner.transfer(uint256(SafeMath.mul(SafeMath.div(seatPrice, 100), SafeMath.div(100, SafeMath.div(200, 17)))));
    participant[2].owner.transfer(uint256(SafeMath.mul(SafeMath.div(seatPrice, 100), SafeMath.div(100, SafeMath.div(200, 17)))));
    participant[3].owner.transfer(uint256(SafeMath.mul(SafeMath.div(seatPrice, 100), SafeMath.div(100, SafeMath.div(200, 17)))));
    participant[4].owner.transfer(uint256(SafeMath.mul(SafeMath.div(seatPrice, 100), SafeMath.div(100, SafeMath.div(200, 17)))));
    participant[5].owner.transfer(uint256(SafeMath.mul(SafeMath.div(seatPrice, 100), SafeMath.div(100, SafeMath.div(200, 17)))));
    participant[6].owner.transfer(uint256(SafeMath.mul(SafeMath.div(seatPrice, 100), SafeMath.div(100, SafeMath.div(200, 17)))));
    participant[7].owner.transfer(uint256(SafeMath.mul(SafeMath.div(seatPrice, 100), SafeMath.div(100, SafeMath.div(200, 17)))));
    participant[8].owner.transfer(uint256(SafeMath.mul(SafeMath.div(seatPrice, 100), SafeMath.div(100, SafeMath.div(200, 17)))));
    participant[9].owner.transfer(uint256(SafeMath.mul(SafeMath.div(seatPrice, 100), SafeMath.div(100, SafeMath.div(200, 17)))));
    participant[10].owner.transfer(uint256(SafeMath.mul(SafeMath.div(seatPrice, 100), SafeMath.div(100, SafeMath.div(200, 17)))));
    participant[10] = participant[9];
    participant[9] = participant[8];
    participant[8] = participant[7];
    participant[7] = participant[6];
    participant[6] = participant[5];
    participant[5] = participant[4];
    participant[4] = participant[3];
    participant[3] = participant[2];
    participant[2] = participant[1];
    participant[1] = Cost(msg.sender, seatPrice);
    adminAddress.transfer(uint256(SafeMath.mul(SafeMath.div(seatPrice, 100), SafeMath.div(100, SafeMath.div(200, 17)))));
    NewParticipant(msg.sender, seatPrice, SafeMath.mul(SafeMath.div(seatPrice, 100), 115));
    seatPrice = SafeMath.mul(SafeMath.div(seatPrice, 100), 115);
    msg.sender.transfer(excess);
}

library SafeMath {
    function mul(uint256 a, uint256 b) internal pure returns(uint256) {
        if (a == 0) {
            return 0;
        }
        uint256 c = a * b;
        assert(c / a == b);
        return c;
    }

    function div(uint256 a, uint256 b) internal pure returns(uint256) {
        uint256 c = a / b;
        return c;
    }

    function sub(uint256 a, uint256 b) internal pure returns(uint256) {
        assert(b <= a);
        return a - b;
    }

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
