 

 
pragma solidity ^0.4.0;

contract Government {

      
     uint32 public lastCreditorPayedOut;
     uint public lastTimeOfNewCredit;
     uint public profitFromCrash;
     address[] public creditorAddresses;
     uint[] public creditorAmounts;
     address public corruptElite;
     mapping (address => uint) buddies;
     uint constant TWELVE_HOURS = 43200;
     uint8 public round;


  using SafeMath for uint;

  uint public contractBalance;
  uint public houseEdge;
  uint public maxProfit;
  uint public maxProfitAsPercentOfHouse;
  uint constant public houseEdgeDivisor = 1000;

  ZTHInterface public ZTHTKN;

  event LogResult(address player, uint result, uint rollUnder, uint profit, uint tokensBetted, bool won);

  struct playerRoll {
    uint200 tokenValue;
    uint48 blockn;
    uint8 rollUnder;
  }

  mapping(address => playerRoll) public playerRolls;

  function random(uint256 upper, uint256 blockn, address entropy) internal view returns (uint256 randomNumber) {
    return maxRandom(blockn, entropy) % upper;
  }

  function maxRandom(uint blockn, address entropy) public view returns (uint256 randomNumber) {
    return uint256(keccak256(
        abi.encodePacked(
        blockhash(blockn),
        entropy)
      ));
  }

  function calculateProfit(uint _initBet, uint _roll)
    private
    view
    returns (uint)
  {
    return ((((_initBet * (100 - (_roll.sub(1)))) / (_roll.sub(1)) + _initBet)) * houseEdge / houseEdgeDivisor) - _initBet;
  }

  function _finishBet(bool delete_it, address target) private returns (uint){
    playerRoll memory roll = playerRolls[target];
    require(roll.tokenValue > 0); // No re-entracy
    require(roll.blockn != block.number);
    uint result;
    if (block.number - roll.blockn > 255) {
      result = 1000;
    } else {
      result = random(99, roll.blockn, target) + 1;
    }

    uint rollUnder = roll.rollUnder;

    if (result < rollUnder) {
      uint profit = calculateProfit(roll.tokenValue, rollUnder);
      
      if (profit > maxProfit){
        profit = maxProfit;
      }

      contractBalance = contractBalance.sub(profit);

      emit LogResult(target, result, rollUnder, profit, roll.tokenValue, true);

      setMaxProfit();

      playerRolls[target] = playerRoll(uint200(0), uint48(0), uint8(0));

      ZTHTKN.transfer(target, profit + roll.tokenValue);
      
      return result;

    } else {
      emit LogResult(target, result, rollUnder, 0, roll.tokenValue, false);

      contractBalance = contractBalance.add(roll.tokenValue);

      playerRolls[target] = playerRoll(uint200(0), uint48(0), uint8(0));

      setMaxProfit();
      
      return result;
    }
  }

  function setMaxProfit() internal {
    maxProfit = (contractBalance * maxProfitAsPercentOfHouse) / 1000000;
  }

     function Government() {
          
          
         profitFromCrash = msg.value;
         corruptElite = msg.sender;
         lastTimeOfNewCredit = block.timestamp;
     }

     function lendGovernmentMoney(address buddy) returns (bool) {
         uint amount = msg.value;
          
          
         if (lastTimeOfNewCredit + TWELVE_HOURS < block.timestamp) {
              
             msg.sender.send(amount);
              
             creditorAddresses[creditorAddresses.length - 1].send(profitFromCrash);
             corruptElite.send(this.balance);
              
             lastCreditorPayedOut = 0;
             lastTimeOfNewCredit = block.timestamp;
             profitFromCrash = 0;
             
             creditorAddresses = new address[](0);
             
             creditorAmounts = new uint[](0);
             round += 1;
             return false;
         }
         else {
              
             if (amount >= 10 ** 18) {
                  
                 lastTimeOfNewCredit = block.timestamp;
                  
                 creditorAddresses.push(msg.sender);
                 creditorAmounts.push(amount * 110 / 100);
                  
                  
                 corruptElite.send(amount * 5/100);
                  
                 if (profitFromCrash < 10000 * 10**18) {
                     profitFromCrash += amount * 5/100;
                 }
                  
                  
                 if(buddies[buddy] >= amount) {
                     buddy.send(amount * 5/100);
                 }
                 buddies[msg.sender] += amount * 110 / 100;
                  
                 if (creditorAmounts[lastCreditorPayedOut] <= address(this).balance - profitFromCrash) {
                     creditorAddresses[lastCreditorPayedOut].send(creditorAmounts[lastCreditorPayedOut]);
                     buddies[creditorAddresses[lastCreditorPayedOut]] -= creditorAmounts[lastCreditorPayedOut];
                     lastCreditorPayedOut += 1;
                 }
                 return true;
             }
             else {
                 msg.sender.send(amount);
                 return false;
             }
         }
     }

      
     function() {
         lendGovernmentMoney(0);
     }

     function totalDebt() returns (uint debt) {
         for(uint i=lastCreditorPayedOut; i<creditorAmounts.length; i++){
             debt += creditorAmounts[i];
         }
     }

     function totalPayedOut() returns (uint payout) {
         for(uint i=0; i<lastCreditorPayedOut; i++){
             payout += creditorAmounts[i];
         }
     }

      
     function investInTheSystem() {
         profitFromCrash += msg.value;
     }

      
     function inheritToNextGeneration(address nextGeneration) {
         if (msg.sender == corruptElite) {
             corruptElite = nextGeneration;
         }
     }

     function getCreditorAddresses() returns (address[]) {
         return creditorAddresses;
     }

     function getCreditorAmounts() returns (uint[]) {
         return creditorAmounts;
     }
 }
