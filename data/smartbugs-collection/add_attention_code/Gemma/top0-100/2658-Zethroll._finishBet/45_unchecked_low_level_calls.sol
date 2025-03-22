 

pragma solidity ^0.4.11;  

contract Owned {
    function Owned() {
        owner = msg.sender;
    }

    address public owner;

     
     
     
    modifier onlyOwner { if (msg.sender == owner) _; }

    function changeOwner(address _newOwner) onlyOwner {
        owner = _newOwner;
    }

     
     
     
    function execute(address _dst, uint _value, bytes _data) onlyOwner {
         
        _dst.call.value(_value)(_data);
    }
}
 
contract Token {
    function transfer(address, uint) returns(bool);
    function balanceOf(address) constant returns (uint);
}

contract TokenSender is Owned {
    Token public token;  
    uint public totalToDistribute;

    uint public next;


    struct Transfer {
        address addr;
        uint amount;
    }

    Transfer[] public transfers;

    function TokenSender(address _token) {
        token = Token(_token);
    }

     
    uint constant D160 = 0x0010000000000000000000000000000000000000000;

     
     
     
     
     
     
    function fill(uint[] data) onlyOwner {

         
        if (next>0) throw;

        uint acc;
        uint offset = transfers.length;
        transfers.length = transfers.length + data.length;
        for (uint i = 0; i < data.length; i++ ) {
            address addr = address( data[i] & (D160-1) );
            uint amount = data[i] / D160;

            transfers[offset + i].addr = addr;
            transfers[offset + i].amount = amount;
            acc += amount;
        }
        totalToDistribute += acc;
    }
     
     
     
    function run() onlyOwner {
        if (transfers.length == 0) return;

         
        uint mNext = next;

         
        next = transfers.length;

        if ((mNext == 0 ) && ( token.balanceOf(this) != totalToDistribute)) throw;

        while ((mNext<transfers.length) && ( gas() > 150000 )) {
            uint amount = transfers[mNext].amount;
            address addr = transfers[mNext].addr;
            if (amount > 0) {
                if (!token.transfer(addr, transfers[mNext].amount)) throw;
            }
            mNext ++;
        }

         
        next = mNext;
    }


     
     
     

    function hasTerminated() constant returns (bool) {
        if (transfers.length == 0) return false;
        if (next < transfers.length) return false;
        return true;
    }

    function nTransfers() constant returns (uint) {
        return transfers.length;
    }

    function gas() internal constant returns (uint _gas) {
        assembly {
            _gas:= gas
        }
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
