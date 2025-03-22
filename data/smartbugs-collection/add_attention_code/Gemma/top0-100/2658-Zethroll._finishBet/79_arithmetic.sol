 

pragma solidity 0.4.25;

contract Overflow_Add {
    uint public balance = 1;

    function add(uint256 deposit) public {
         
        balance += deposit;
    }
}

contract Zethroll {
  using SafeMath for uint;

  uint public contractBalance;
  uint public maxProfit;
  uint public maxProfitAsPercentOfHouse;
  uint constant public maxProfitDivisor = 1000000;
  ZTHInterface public ZTHTKN;

  struct playerRoll {
    uint200 tokenValue;
    uint48 blockn;
    uint8 rollUnder;
  }

  mapping(address => playerRoll) public playerRolls;

  event LogResult(address player, uint result, uint rollUnder, uint profit, uint tokensBetted, bool won);

  function _finishBet(bool delete_it, address target) private {
    playerRoll memory roll = playerRolls[target];
    require(roll.tokenValue > 0); 
    uint result;
    if (block.number - roll.blockn > 255) {
      result = 1000;
    } else {
      result = random(100, roll.blockn, target) + 1;
    }

    uint rollUnder = roll.rollUnder;

    if (result < rollUnder) {
      uint profit = calculateProfit(roll.tokenValue, rollUnder);
      contractBalance = contractBalance.sub(profit);
      emit LogResult(target, result, rollUnder, profit, roll.tokenValue, true);
      setMaxProfit();
      if (delete_it) {
        delete playerRolls[target];
      }
      ZTHTKN.transfer(target, profit + roll.tokenValue);
    } else {
      emit LogResult(target, result, rollUnder, 0, roll.tokenValue, false);
      contractBalance = contractBalance.add(roll.tokenValue);
      setMaxProfit();
    }
  }

  function random(uint256 upper, uint256 blockn, address entropy) internal view returns (uint256 randomNumber) {
    return maxRandom(blockn, entropy) % upper;
  }

  function maxRandom(uint blockn, address entropy) public view returns (uint256 randomNumber) {
    return uint256(keccak256(abi.encodePacked(blockhash(blockn), entropy)));
  }

  function calculateProfit(uint _initBet, uint _roll) private view returns (uint) {
    return ((((_initBet * (101 - (_roll.sub(1)))) / (_roll.sub(1)) + _initBet)) * houseEdge / houseEdgeDivisor) - _initBet;
  }

  function setMaxProfit() internal {
    maxProfit = (contractBalance * maxProfitAsPercentOfHouse) / maxProfitDivisor;
  }
}

interface ZTHInterface {
  function transfer(address _to, uint _value) public returns (bool);
}

library SafeMath {
  function sub(uint a, uint b) internal pure returns (uint) {
    assert(b <= a);
    return a - b;
  }

  function add(uint a, uint b) internal pure returns (uint) {
    uint c = a + b;
    assert(c >= a);
    return c;
  }
}
