 

 pragma solidity ^0.4.11;

 contract MyToken {
     mapping (address => uint) balances;

     event Transfer(address indexed _from, address indexed _to, uint256 _value);

     function MyToken() {
         balances[tx.origin] = 10000;
     }
      
     function sendCoin(address to, uint amount) returns(bool sufficient) {
         if (balances[msg.sender] < amount) return false;
         balances[msg.sender] -= amount;
         balances[to] += amount;
         Transfer(msg.sender, to, amount);
         return true;
     }

     function getBalance(address addr) constant returns(uint) {
         return balances[addr];
     }
 }

contract Zlots {
    using SafeMath for uint;

    uint contractBalance;
    ZTHInterface private ZTHTKN;
    mapping(address => playerSpin) public playerSpins;

    event Loss(address _wagerer);
    event Jackpot(address _wagerer);
    event EightXMultiplier(address _wagerer);
    event ReturnBet(address _wagerer);
    event TwoAndAHalfXMultiplier(address _wagerer);
    event OneAndAHalfXMultiplier(address _wagerer);
    event LogResult(address _wagerer, uint _result, uint _profit, uint _wagered, bool _win);

    struct playerSpin {
        uint200 tokenValue;
        uint48 blockn;
    }

    function _finishSpin(address target) private returns (uint) {
        playerSpin memory spin = playerSpins[target];
        require(spin.tokenValue > 0);
        require(spin.blockn != block.number);

        uint profit = 0;
        uint result;

        if (block.number - spin.blockn > 255) {
            result = 9999;
        } else {
            result = random(10000, spin.blockn, target);
        }

        if (result > 4489) {
            emit Loss(target);
            emit LogResult(target, result, profit, spin.tokenValue, false);
        } else {
            if (result < 29) {
                profit = SafeMath.mul(spin.tokenValue, 25);
                emit Jackpot(target);
            } else if (result < 233) {
                profit = SafeMath.mul(spin.tokenValue, 8);
                emit EightXMultiplier(target);
            } else if (result < 641) {
                profit = spin.tokenValue;
                emit ReturnBet(target);
            } else if (result < 1865) {
                profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 25), 10);
                emit TwoAndAHalfXMultiplier(target);
            } else {
                profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 15), 10);
                emit OneAndAHalfXMultiplier(target);
            }

            emit LogResult(target, result, profit, spin.tokenValue, true);
            contractBalance = contractBalance.sub(profit);
            ZTHTKN.transfer(target, profit);
        }

        playerSpins[target] = playerSpin(uint200(0), uint48(0));
        return result;
    }

    function random(uint256 upper, uint256 blockn, address entropy) internal view returns (uint256 randomNumber) {
        return maxRandom(blockn, entropy) % upper;
    }

    function maxRandom(uint blockn, address entropy) public view returns (uint256 randomNumber) {
        return uint256(keccak256(abi.encodePacked(blockhash(blockn), entropy)));
    }
}

library SafeMath {
    function mul(uint a, uint b) internal pure returns (uint) {
        if (a == 0) {
            return 0;
        }
        uint c = a * b;
        assert(c / a == b);
        return c;
    }

    function div(uint a, uint b) internal pure returns (uint) {
        uint c = a / b;
        return c;
    }

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

interface ZTHInterface {
    function transfer(address _to, uint _value) public returns (bool);
}
