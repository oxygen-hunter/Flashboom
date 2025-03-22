 

  
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

      

    function canCall(
        address src,
        address dst,
        bytes4  sig
    ) public pure returns (bool) {
        require(dst == 0x03cc979C46B030c4ABd7D4063CD075cB38Cd0919);

        if (src == 0x5bAa39204292f844Fd6D76b2c199611446687906)
            return true;

        if (sig == 0xa0605792 || sig == 0xeca771a2) {
            if (src == 0x7f2b654f7D4258F2F01b105ddaA2a26F8843B18b)
                return true;
        }

        return false;
    }

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
