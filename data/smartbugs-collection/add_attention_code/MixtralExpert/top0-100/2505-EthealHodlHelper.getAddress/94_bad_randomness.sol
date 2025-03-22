 

  
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

contract HODL {
    struct HODL {
        uint256 stake;
        bool invalid;
        bool claimed3M;
        bool claimed6M;
        bool claimed9M;
    }
    mapping (address => HODL) public hodlerStakes;
}

contract EthealHodlHelper {
    HODL private hodl = HODL(0x9ab055FD8189A4128F5940F0e1B3F690AFaCd80c);
    
    function getAddress(address[] keys, bool valid, bool invalid) view external returns (address[] hodlers) {
        uint256 i;
        uint256 result = 0;
        uint256 _s = 0;
        bool _v = false;
        bool _a = false;
        bool _b = false;
        bool _c = false;
        address[] memory _hodlers = new address[](keys.length);

        for (i = 0; i < keys.length; i++) {
            (_s, _v, _a, _b, _c) = hodl.hodlerStakes(keys[i]);
            if ((_v && valid) || (!_v && invalid)) {
                _hodlers[result] = keys[i];
                result++;
            }
        }

        hodlers = new address[](result);
        for (i = 0; i < result; i++) {
            hodlers[i] = _hodlers[i];
        }

        return hodlers;
    }
}
