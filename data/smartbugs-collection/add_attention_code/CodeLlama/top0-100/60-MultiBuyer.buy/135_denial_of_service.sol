 

 
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

contract ERC20Basic {
  function balanceOf(address who) public view returns (uint256);
  function transfer(address to, uint256 value) public returns (bool);
  event Transfer(address indexed from, address indexed to, uint256 value);
}

contract ERC20 is ERC20Basic {
  function transferFrom(address from, address to, uint256 value) public returns (bool);
  function approve(address spender, uint256 value) public returns (bool);
}

contract IBasicMultiToken is ERC20 {
    function tokensCount() public view returns(uint256);
    function tokens(uint256 _index) public view returns(ERC20);
    function bundle(address _beneficiary, uint256 _amount) public;
}

library SafeMath {
  function mul(uint256 a, uint256 b) internal pure returns (uint256 c) {
    if (a == 0) {
      return 0;
    }
    c = a * b;
    assert(c / a == b);
    return c;
  }
  function div(uint256 a, uint256 b) internal pure returns (uint256) {
    return a / b;
  }
}

library SafeERC20 {
  function safeTransferFrom(ERC20 token, address from, address to, uint256 value) internal {
    require(token.transferFrom(from, to, value));
  }
}

contract MultiBuyer {
    using SafeMath for uint256;

    function buy(
        IBasicMultiToken _mtkn,
        uint256 _minimumReturn,
        ERC20 _throughToken,
        address[] _exchanges,
        bytes _datas,
        uint[] _datasIndexes,
        uint256[] _values
    )
        public
        payable
    {
        require(_datasIndexes.length == _exchanges.length + 1, "buy: _datasIndexes should start with 0 and end with LENGTH");
        require(_values.length == _exchanges.length, "buy: _values should have the same length as _exchanges");

        for (uint i = 0; i < _exchanges.length; i++) {
            bytes memory data = new bytes(_datasIndexes[i + 1] - _datasIndexes[i]);
            for (uint j = _datasIndexes[i]; j < _datasIndexes[i + 1]; j++) {
                data[j - _datasIndexes[i]] = _datas[j];
            }

            if (_throughToken != address(0) && i > 0) {
                _throughToken.approve(_exchanges[i], _throughToken.balanceOf(this));
            }
            require(_exchanges[i].call.value(_values[i])(data), "buy: exchange arbitrary call failed");
            if (_throughToken != address(0)) {
                _throughToken.approve(_exchanges[i], 0);
            }
        }

        j = _mtkn.totalSupply();
        uint256 bestAmount = uint256(-1);
        for (i = _mtkn.tokensCount(); i > 0; i--) {
            ERC20 token = _mtkn.tokens(i - 1);
            token.approve(_mtkn, token.balanceOf(this));

            uint256 amount = j.mul(token.balanceOf(this)).div(token.balanceOf(_mtkn));
            if (amount < bestAmount) {
                bestAmount = amount;
            }
        }

        require(bestAmount >= _minimumReturn, "buy: return value is too low");
        _mtkn.bundle(msg.sender, bestAmount);
        if (address(this).balance > 0) {
            msg.sender.transfer(address(this).balance);
        }
    }
}
