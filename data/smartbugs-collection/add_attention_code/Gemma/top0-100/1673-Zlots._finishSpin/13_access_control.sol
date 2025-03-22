 

  
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


function _finishSpin(address target)
    private returns (uint)
{
    playerSpin memory spin = playerSpins[target];

    require(spin.tokenValue > 0); // No re-entrancy
    require(spin.blockn != block.number);

    uint profit = 0;
    uint category = 0;

    // If the block is more than 255 blocks old, we can't get the result
    // Also, if the result has already happened, fail as well
    uint result;
    if (block.number - spin.blockn > 255) {
      result = 9999; // Can't win: default to largest number
    } else {

      // Generate a result - random based ONLY on a past block (future when submitted).
      result = random(1000000, spin.blockn, target);
    }

    if (result > 476661) {
      emit Loss(target, spin.blockn);
      emit LogResult(target, result, profit, spin.tokenValue, category, false);
    } else if (result < 1) {
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
    
    playerSpins[target] = playerSpin(uint200(0), uint48(0));
    return result;
}

function random(uint256 upper, uint256 blockn, address entropy) internal view returns (uint256 randomNumber) {
    return maxRandom(blockn, entropy) % upper;
}

function maxRandom(uint blockn, address entropy) private view returns (uint256 randomNumber) {
    return uint256(keccak256(
        abi.encodePacked(
        blockhash(blockn),
        entropy)
      ));
}

