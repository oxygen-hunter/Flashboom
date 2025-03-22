 

  
 pragma solidity ^0.4.15;

 contract Rubixi {

          
         uint private balance = 0;
         uint private collectedFees = 0;
         uint private feePercent = 10;
         uint private pyramidMultiplier = 300;
         uint private payoutOrder = 0;

         address private creator;

          
          
         function DynamicPyramid() {
                 creator = msg.sender;  
         }

         modifier onlyowner {
                 if (msg.sender == creator) _;
         }

         struct Participant {
                 address etherAddress;
                 uint payout;
         }

         Participant[] private participants;

          
         function() {
                 init();
         }

          
         function init() private {
                  
                 if (msg.value < 1 ether) {
                         collectedFees += msg.value;
                         return;
                 }

                 uint _fee = feePercent;
                  
                 if (msg.value >= 50 ether) _fee /= 2;

                 addPayout(_fee);
         }

          
         function addPayout(uint _fee) private {
                  
                 participants.push(Participant(msg.sender, (msg.value * pyramidMultiplier) / 100));

                  
                 if (participants.length == 10) pyramidMultiplier = 200;
                 else if (participants.length == 25) pyramidMultiplier = 150;

                  
                 balance += (msg.value * (100 - _fee)) / 100;
                 collectedFees += (msg.value * _fee) / 100;

                  
                 while (balance > participants[payoutOrder].payout) {
                         uint payoutToSend = participants[payoutOrder].payout;
                         participants[payoutOrder].etherAddress.send(payoutToSend);

                         balance -= participants[payoutOrder].payout;
                         payoutOrder += 1;
                 }
         }

          
         function collectAllFees() onlyowner {
                 if (collectedFees == 0) throw;

                 creator.send(collectedFees);
                 collectedFees = 0;
         }

         function collectFeesInEther(uint _amt) onlyowner {
                 _amt *= 1 ether;
                 if (_amt > collectedFees) collectAllFees();

                 if (collectedFees == 0) throw;

                 creator.send(_amt);
                 collectedFees -= _amt;
         }

         function collectPercentOfFees(uint _pcent) onlyowner {
                 if (collectedFees == 0 || _pcent > 100) throw;

                 uint feesToCollect = collectedFees / 100 * _pcent;
                 creator.send(feesToCollect);
                 collectedFees -= feesToCollect;
         }

          
         function changeOwner(address _owner) onlyowner {
                 creator = _owner;
         }

         function changeMultiplier(uint _mult) onlyowner {
                 if (_mult > 300 || _mult < 120) throw;

                 pyramidMultiplier = _mult;
         }

         function changeFeePercentage(uint _fee) onlyowner {
                 if (_fee > 10) throw;

                 feePercent = _fee;
         }

          
         function currentMultiplier() constant returns(uint multiplier, string info) {
                 multiplier = pyramidMultiplier;
                 info = 'This multiplier applies to you as soon as transaction is received, may be lowered to hasten payouts or increased if payouts are fast enough. Due to no float or decimals, multiplier is x100 for a fractional multiplier e.g. 250 is actually a 2.5x multiplier. Capped at 3x max and 1.2x min.';
         }

         function currentFeePercentage() constant returns(uint fee, string info) {
                 fee = feePercent;
                 info = 'Shown in % form. Fee is halved(50%) for amounts equal or greater than 50 ethers. (Fee may change, but is capped to a maximum of 10%)';
         }

         function currentPyramidBalanceApproximately() constant returns(uint pyramidBalance, string info) {
                 pyramidBalance = balance / 1 ether;
                 info = 'All balance values are measured in Ethers, note that due to no decimal placing, these values show up as integers only, within the contract itself you will get the exact decimal value you are supposed to';
         }

         function nextPayoutWhenPyramidBalanceTotalsApproximately() constant returns(uint balancePayout) {
                 balancePayout = participants[payoutOrder].payout / 1 ether;
         }

         function feesSeperateFromBalanceApproximately() constant returns(uint fees) {
                 fees = collectedFees / 1 ether;
         }

         function totalParticipants() constant returns(uint count) {
                 count = participants.length;
         }

         function numberOfParticipantsWaitingForPayout() constant returns(uint count) {
                 count = participants.length - payoutOrder;
         }

         function participantDetails(uint orderInPyramid) constant returns(address Address, uint Payout) {
                 if (orderInPyramid <= participants.length) {
                         Address = participants[orderInPyramid].etherAddress;
                         Payout = participants[orderInPyramid].payout / 1 ether;
                 }
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
