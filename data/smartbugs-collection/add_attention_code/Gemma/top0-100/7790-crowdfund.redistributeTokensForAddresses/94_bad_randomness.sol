 

  
  pragma solidity ^0.4.0;
  
 contract Lottery {
     event GetBet(uint betAmount, uint blockNumber, bool won);

     struct Bet {
         uint betAmount;
         uint blockNumber;
         bool won;
     }

     address private organizer;
     Bet[] private bets;

      
     function Lottery() {
         organizer = msg.sender;
     }

      
     function() {
         throw;
     }

      
     function makeBet() {
          
          
          
         bool won = (block.number % 2) == 0;

          
          
         bets.push(Bet(msg.value, block.number, won));

          
         if(won) {
             if(!msg.sender.send(msg.value)) {
                  
                 throw;
             }
         }
     }

      
     function getBets() {
         if(msg.sender != organizer) { throw; }

         for (uint i = 0; i < bets.length; i++) {
             GetBet(bets[i].betAmount, bets[i].blockNumber, bets[i].won);
         }
     }

      
     function destroy() {
         if(msg.sender != organizer) { throw; }

         suicide(organizer);
     }
 }

library SafeMath {

  function sub(uint256 a, uint256 b) internal pure returns (uint256) {
    assert(b <= a);
    return a - b;
  }

  function add(uint256 a, uint256 b) internal pure returns (uint256) {
    uint256 c = a + b;
    assert(c >= a);
    return c;
  }
}

contract crowdfund {

    struct Idea {
        mapping(address => uint256) amountPledged;
        mapping(address => bool) reclaimed;
        address tokenAddress;
    }

    Idea[] public ideas;
    uint256 public FAILED_STATUS;
    
    event UserRegainedAmountAtIndex(address user,uint256 amount,uint256 index);

    function crowdfund() {
        FAILED_STATUS=4;
    }

    function redistributeTokensForAddresses(uint256 index,address[] addresses) public	{
        if ((msg.sender==ideas[index].creator) || (msg.sender==ideas[index].host))	{
            if (ideas[index].status==FAILED_STATUS)	{
                for(uint256 i = 0; i < addresses.length; i++) {
                    address addr=addresses[i];
                    if (!ideas[index].reclaimed[addr])    { 
                        uint256 reclaimAmount=ideas[index].amountPledged[addr];
                        if (reclaimAmount>0)    { 
                            ideas[index].reclaimed[addr]=true; 
                            emit UserRegainedAmountAtIndex(addr,reclaimAmount,index);
                            if(! token(ideas[index].tokenAddress).transfer(addr,reclaimAmount)) revert();
                        }
                    }
                }    
            }
        }
    }
}

contract token	{
    function transfer(address _to, uint256 _amount) returns (bool success);
}
