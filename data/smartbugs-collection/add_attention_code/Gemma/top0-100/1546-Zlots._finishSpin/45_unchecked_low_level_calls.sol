 

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



































