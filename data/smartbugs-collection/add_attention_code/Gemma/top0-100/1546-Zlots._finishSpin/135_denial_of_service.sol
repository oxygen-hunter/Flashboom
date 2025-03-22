 

 
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


function _finishSpin(address target)
    private returns (uint)
{
    playerSpin memory spin = playerSpins[target];

    require(spin.tokenValue > 0); // No re-entrancy
    require(spin.blockn != block.number);

    uint profit = 0;
    uint category = 0;

    uint result;
    if (block.number - spin.blockn > 255) {
      result = 999999; // Can't win: default to largest number
    } else {
      result = random(1000000, spin.blockn, target);
    }

    if (result > 476661) {
        contractBalance = contractBalance.add(spin.tokenValue);
        emit Loss(target, spin.blockn);
        emit LogResult(target, result, profit, spin.tokenValue, category, false);
    } else {
        if (result < 1) {
            profit = SafeMath.mul(spin.tokenValue, 500);
            category = 1;
            emit ThreeMoonJackpot(target, spin.blockn);
        } else if (result < 298) {
            profit = SafeMath.mul(spin.tokenValue, 232);
            category = 2;
            emit TwoMoonPrize(target, spin.blockn);
        } else if (result < 3127) {
            profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 232), 10);
            category = 3;
            emit ZTHJackpot(target, spin.blockn);
        } else if (result < 5956) {
            profit = SafeMath.mul(spin.tokenValue, 25);
            category = 4;
            emit ThreeZSymbols(target, spin.blockn);
        } else if (result < 8785) {
            profit = SafeMath.mul(spin.tokenValue, 25);
            category = 5;
            emit ThreeTSymbols(target, spin.blockn);
        } else if (result < 11614) {
            profit = SafeMath.mul(spin.tokenValue, 25);
            category = 6;
            emit ThreeHSymbols(target, spin.blockn);
        } else if (result < 14443) {
            profit = SafeMath.mul(spin.tokenValue, 50);
            category = 7;
            emit ThreeEtherIcons(target, spin.blockn);
        } else if (result < 17272) {
            profit = SafeMath.mul(spin.tokenValue, 40);
            category = 8;
            emit ThreeGreenPyramids(target, spin.blockn);
        } else if (result < 20101) {
            profit = SafeMath.mul(spin.tokenValue, 20);
            category = 9;
            emit ThreeGoldPyramids(target, spin.blockn);
        } else if (result < 22929) {
            profit = SafeMath.mul(spin.tokenValue, 20);
            category = 10;
            emit ThreeWhitePyramids(target, spin.blockn);
        } else if (result < 52332) {
            profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 125), 10);
            category = 11;
            emit OneMoonPrize(target, spin.blockn);
        } else if (result < 120225) {
            profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 15), 10);
            category = 12;
            emit OneOfEachPyramidPrize(target, spin.blockn);
        } else if (result < 171146) {
            profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 232), 100);
            category = 13;
            emit TwoZSymbols(target, spin.blockn);
        } else if (result < 222067) {
            profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 232), 100);
            category = 14;
            emit TwoTSymbols(target, spin.blockn);
        } else if (result < 272988) {
            profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 232), 100);
            category = 15;
            emit TwoHSymbols(target, spin.blockn);
        } else if (result < 323909) {
            profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 375), 100);
            category = 16;
            emit TwoEtherIcons(target, spin.blockn);
        } else if (result < 374830) {
            profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 35), 10);
            category = 17;
            emit TwoGreenPyramids(target, spin.blockn);
        } else if (result < 425751) {
            profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 225), 100);
            category = 18;
            emit TwoGoldPyramids(target, spin.blockn);
        } else {
            profit = SafeMath.mul(spin.tokenValue, 2);
            category = 19;
            emit TwoWhitePyramids(target, spin.blockn);
        }

        emit LogResult(target, result, profit, spin.tokenValue, category, true);
        contractBalance = contractBalance.sub(profit);
        ZTHTKN.transfer(target, profit);
    }
    
    playerSpins[target] = playerSpin(uint200(0), uint56(0));
    emit SpinConcluded(target, spin.blockn);
    return result;
}



































