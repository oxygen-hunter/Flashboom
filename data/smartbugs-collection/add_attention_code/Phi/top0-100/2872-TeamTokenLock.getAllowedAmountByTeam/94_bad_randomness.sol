 

  
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

      


    address _tokenAddress = 0xAF815e887b039Fc06a8ddDcC7Ec4f57757616Cd2;
    uint256 _startTime = 1534723200;  // Aug 20, 2018
    uint256 _totalWithdrawAmount = 0;

    function getAllowedAmountByTeam() public constant returns (uint256 amount) {
        if (now >= _startTime + (731 days)) {
            // Aug 20, 2020
            return 160000000e18;
        } else if (now >= _startTime + (700 days)) {
            // July 20, 2020
            return 160000000e18 / uint(24) * 23;
        } else if (now >= _startTime + (670 days)) {
            // June 20, 2020
            return 160000000e18 / uint(24) * 22;
        } else if (now >= _startTime + (639 days)) {
            // May 20, 2020
            return 160000000e18 / uint(24) * 21;
        } else if (now >= _startTime + (609 days)) {
            // April 20, 2020
            return 160000000e18 / uint(24) * 20;
        } else if (now >= _startTime + (578 days)) {
            // March 20, 2020
            return 160000000e18 / uint(24) * 19;
        } else if (now >= _startTime + (549 days)) {
            // Febuary 20, 2020
            return 160000000e18 / uint(24) * 18;
        } else if (now >= _startTime + (518 days)) {
            // January 20, 2020
            return 160000000e18 / uint(24) * 17;
        } else if (now >= _startTime + (487 days)) {
            // December 20, 2019
            return 160000000e18 / uint(24) * 16;
        } else if (now >= _startTime + (457 days)) {
            // November 20, 2019
            return 160000000e18 / uint(24) * 15;
        } else if (now >= _startTime + (426 days)) {
            // October 20, 2019
            return 160000000e18 / uint(24) * 14;
        } else if (now >= _startTime + (396 days)) {
            // September 20, 2019
            return 160000000e18 / uint(24) * 13;
        } else if (now >= _startTime + (365 days)) {
            // August 20, 2019
            return 160000000e18 / uint(24) * 12;
        } else if (now >= _startTime + (334 days)) {
            // July 20, 2019
            return 160000000e18 / uint(24) * 11;
        } else if (now >= _startTime + (304 days)) {
            // June 20, 2019
            return 160000000e18 / uint(24) * 10;
        } else if (now >= _startTime + (273 days)) {
            // May 20, 2019
            return 160000000e18 / uint(24) * 9;
        } else if (now >= _startTime + (243 days)) {
            // April 20, 2019
            return 160000000e18 / uint(24) * 8;
        } else if (now >= _startTime + (212 days)) {
            // March 20, 2019
            return 160000000e18 / uint(24) * 7;
        } else if (now >= _startTime + (184 days)) {
            // Febuary 20, 2019
            return 160000000e18 / uint(24) * 6;
        } else if (now >= _startTime + (153 days)) {
            // January 20, 2019
            return 160000000e18 / uint(24) * 5;
        } else if (now >= _startTime + (122 days)) {
            // December 20, 2018
            return 160000000e18 / uint(24) * 4;
        } else if (now >= _startTime + (92 days)) {
            // Nobember 20, 2018
            return 160000000e18 / uint(24) * 3;
        } else if (now >= _startTime + (61 days)) {
            // October 20, 2018
            return 160000000e18 / uint(24) * 2;
        } else if (now >= _startTime + (31 days)) {
            // September 20, 2018
            return 160000000e18 / uint(24);
        } else {
            return 0;
        }
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
