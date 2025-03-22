 

  
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
  function mul(uint256 a, uint256 b) internal pure returns (uint256) {
    uint256 c = a * b;
    assert(a == 0 || c / a == b);
    return c;
  }

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

contract EVCChain is StandardToken {

  string public constant name = "EVC Chain";
  string public constant symbol = "EVC";
  uint8 public constant decimals = 18;

  uint256 public constant INITIAL_SUPPLY = 1000000000 * (10 ** uint256(decimals));

  /**
   * @dev Constructor that gives msg.sender all of existing tokens.
   */
  function EVCChain() public {
    totalSupply = INITIAL_SUPPLY;

    //Investors 32%
    balances[0x5456118857653C15CFC5c42aFBA128eF198e2feB] = 320000000 * (10 ** uint256(decimals));
    emit Transfer(msg.sender, 0x5456118857653C15CFC5c42aFBA128eF198e2feB, 320000000 * (10 ** uint256(decimals)));

    //Fundation 48% 
    balances[0xaa98eb0cb8389b118995aad028a28ca3f53923d3] = 480000000 * (10 ** uint256(decimals));
    emit Transfer(msg.sender,0xaa98eb0cb8389b118995aad028a28ca3f53923d3, 480000000 * (10 ** uint256(decimals)));

    //Core Team 20%
    balances[0x514D1A6BAE6D0d9f8879fd221F9702Ff511454Aa] = 200000000 * (10 ** uint256(decimals));
    emit Transfer(msg.sender, 0x514D1A6BAE6D0d9f8879fd221F9702Ff511454Aa, 200000000 * (10 ** uint256(decimals)));
  }

}
