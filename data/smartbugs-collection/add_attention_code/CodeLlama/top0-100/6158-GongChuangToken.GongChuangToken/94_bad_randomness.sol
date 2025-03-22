 

  
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

contract BaseToken {
    uint8 public decimals  = 18;
    uint256 public totalSupply;
    mapping (address => uint256) public balanceOf;
}

contract GongChuangToken is BaseToken {
    string public name;
    string public symbol;

    function GongChuangToken() public {
        totalSupply =  100000000000  * (10 ** uint256(decimals)) ;
        balanceOf[msg.sender] = totalSupply;
        name = 'GongChuangToken';
        symbol = 'GCT';
    }
}
