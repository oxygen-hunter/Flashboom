 

  
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

library SafeMath {
    function add(uint256 a, uint256 b) internal pure returns (uint256 c) {
        c = a + b;
        require(c >= a);
    }

    function sub(uint256 a, uint256 b) internal pure returns (uint256 c) {
        require(b <= a);
        c = a - b;
    }

    function div(uint256 a, uint256 b) internal pure returns (uint256 c) {
        require(b > 0);
        c = a / b;
    }

    function mul(uint256 a, uint256 b) internal pure returns (uint256 c) {
        c = a * b;
        require(a == 0 || c / a == b);
    }
}

contract Queue {
    using SafeMath for uint256;
    address[] users;
    mapping(address => bool) usersExist;
    mapping(address => address) users2users;
    mapping(address => uint256) collectBalances;
    mapping(address => uint256) balances;
    mapping(address => uint256) balancesTotal;
    uint256 nextForwardUserId = 0;
    uint256 nextBackUserId = 0;
    uint256 cyles = 50;
    uint256 interes = 10 finney;
    uint256 reminder = 0;
    uint256 queueInteres = 100 szabo;
    address to;
    uint256 collect = 30 finney;
    uint256 referalBonus = 5 finney;

    event QueueStart(address indexed user, address indexed parentUser, uint256 indexed timeshtamp);
    event BalanceUp(address indexed user, uint256 amount, uint256 indexed timeshtamp);

    function serchIndexByAddress(address a) public view returns (uint256 index) {
        for(index=0; index<users.length; index++) {
            if(a == users[index]){
                return index;
            }
        }
    }

    function _removeIndex(uint256 indexToRemove) internal {
        if (indexToRemove >= users.length) return;

        for (uint i = indexToRemove; i < users.length - 1; i++){
            users[i] = users[i + 1];
        }
        delete users[users.length - 1];
        users.length--;
    }

    function _queue(address user, address parentUser) internal {
        if (user != address(0x9a965e5e9c3A0F062C80a7f3d1B0972201b2F19f) ) {
            require(parentUser != user);
            require(usersExist[parentUser]);
        }
        users.push(user);
        usersExist[user] = true;
        users2users[user] = parentUser;
        emit QueueStart(user, parentUser, now);

        if (collectBalances[parentUser].add(referalBonus) >= collect) {
            reminder = collectBalances[parentUser].add(referalBonus) - collect;
            balancesTotal[parentUser] = balancesTotal[parentUser].add(interes);
            balances[parentUser] = balances[parentUser].add(interes);
            emit BalanceUp(parentUser, interes, now);
            collectBalances[parentUser] = reminder;
            to = parentUser;
            _removeIndex(serchIndexByAddress(parentUser));
            _queue(to, users2users[to]);
        } else {
            collectBalances[parentUser] = collectBalances[parentUser].add(referalBonus);
        }

        if (collectBalances[users2users[parentUser]].add(referalBonus) >= collect) {
            reminder = collectBalances[users2users[parentUser]].add(referalBonus) - collect;
            balancesTotal[users2users[parentUser]] = balancesTotal[users2users[parentUser]].add(interes);
            balances[users2users[parentUser]] = balances[users2users[parentUser]].add(interes);
            emit BalanceUp(users2users[parentUser], interes, now);
            collectBalances[users2users[parentUser]] = reminder;
            to = users2users[parentUser];
            _removeIndex(serchIndexByAddress(users2users[parentUser]));
            _queue(to, users2users[to]);
        } else {
            collectBalances[users2users[parentUser]] = collectBalances[users2users[parentUser]].add(referalBonus);
        }

        uint256 length = users.length;
        uint256 existLastIndex = length.sub(1);
        uint256 firstHalfEnd = 0;
        uint256 secondHalfStart = 0;

        if (length == 1) {
            collectBalances[users[0]] = collectBalances[users[0]].add(queueInteres.mul(cyles.mul(2)));
        } else {
            if (length % 2 != 0) {
                firstHalfEnd  = length.div(2);
                secondHalfStart  = length.div(2);
            } else {
                firstHalfEnd  = length.div(2).sub(1);
                secondHalfStart  = length.div(2);
            }

            for (uint i = 1; i <= cyles; i++) {
                if (collectBalances[users[nextForwardUserId]].add(queueInteres) >= collect) {
                    reminder = collectBalances[users[nextForwardUserId]].add(queueInteres) - collect;
                    balancesTotal[users[nextForwardUserId]] = balancesTotal[users[nextForwardUserId]].add(interes);
                    balances[users[nextForwardUserId]] = balances[users[nextForwardUserId]].add(interes);
                    collectBalances[users[nextForwardUserId]] = reminder;
                    emit BalanceUp(users[nextForwardUserId], interes, now);
                    to = users[nextForwardUserId];
                    _removeIndex(serchIndexByAddress(users[nextForwardUserId]));
                    _queue(to, users2users[to]);
                    if (nextForwardUserId == 0) {
                        nextForwardUserId = firstHalfEnd;
                    } else {
                        nextForwardUserId = nextForwardUserId.sub(1);
                    }
                } else {
                    collectBalances[users[nextForwardUserId]] = collectBalances[users[nextForwardUserId]].add(queueInteres);
                }

                if (collectBalances[users[nextBackUserId]].add(queueInteres) == collect) {
                    reminder = collectBalances[users[nextBackUserId]].add(queueInteres) - collect;
                    balancesTotal[users[nextBackUserId]] = balancesTotal[users[nextBackUserId]].add(interes);
                    balances[users[nextBackUserId]] = balances[users[nextBackUserId]].add(interes);
                    collectBalances[users[nextBackUserId]] = reminder;
                    emit BalanceUp(users[nextBackUserId], interes, now);
                    to = users[nextBackUserId];
                    _removeIndex(serchIndexByAddress(users[nextBackUserId]));
                    _queue(to, users2users[to]);
                    if (nextBackUserId == existLastIndex) {
                        nextBackUserId = secondHalfStart;
                    } else {
                        nextBackUserId = nextBackUserId.add(1);
                    }
                } else {
                    collectBalances[users[nextBackUserId]] = collectBalances[users[nextBackUserId]].add(queueInteres);
                }
            }
        }
    }
}
