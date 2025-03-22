 

 
 
 
 
 

 
 
 

 
 
 
 
 

 
pragma solidity ^0.4.0;

contract KingOfTheEtherThrone {

    struct Monarch {
         
        address etherAddress;
         
         
        string name;
         
        uint claimPrice;
         
        uint coronationTimestamp;
    }

     
     
    address wizardAddress;

     
    modifier onlywizard { if (msg.sender == wizardAddress) _; }

     
    uint constant startingClaimPrice = 100 finney;

     
     
     
    uint constant claimPriceAdjustNum = 3;
    uint constant claimPriceAdjustDen = 2;

     
     
     
    uint constant wizardCommissionFractionNum = 1;
    uint constant wizardCommissionFractionDen = 100;

     
    uint public currentClaimPrice;

     
    Monarch public currentMonarch;

     
    Monarch[] public pastMonarchs;

     
     
    function KingOfTheEtherThrone() {
        wizardAddress = msg.sender;
        currentClaimPrice = startingClaimPrice;
        currentMonarch = Monarch(
            wizardAddress,
            "[Vacant]",
            0,
            block.timestamp
        );
    }

    function numberOfMonarchs() constant returns (uint n) {
        return pastMonarchs.length;
    }

     
     
    event ThroneClaimed(
        address usurperEtherAddress,
        string usurperName,
        uint newClaimPrice
    );

     
     
    function() {
        claimThrone(string(msg.data));
    }

     
    function claimThrone(string name) {

        uint valuePaid = msg.value;

         
        if (valuePaid < currentClaimPrice) {
             
            msg.sender.send(valuePaid);
            return;
        }

         
        if (valuePaid > currentClaimPrice) {
            uint excessPaid = valuePaid - currentClaimPrice;
             
            msg.sender.send(excessPaid);
            valuePaid = valuePaid - excessPaid;
        }

         
         
         

        uint wizardCommission = (valuePaid * wizardCommissionFractionNum) / wizardCommissionFractionDen;

        uint compensation = valuePaid - wizardCommission;

        if (currentMonarch.etherAddress != wizardAddress) {
             
            currentMonarch.etherAddress.send(compensation);
        } else {
             
        }

         
        pastMonarchs.push(currentMonarch);
        currentMonarch = Monarch(
            msg.sender,
            name,
            valuePaid,
            block.timestamp
        );

         
         
        uint rawNewClaimPrice = currentClaimPrice * claimPriceAdjustNum / claimPriceAdjustDen;
        if (rawNewClaimPrice < 10 finney) {
            currentClaimPrice = rawNewClaimPrice;
        } else if (rawNewClaimPrice < 100 finney) {
            currentClaimPrice = 100 szabo * (rawNewClaimPrice / 100 szabo);
        } else if (rawNewClaimPrice < 1 ether) {
            currentClaimPrice = 1 finney * (rawNewClaimPrice / 1 finney);
        } else if (rawNewClaimPrice < 10 ether) {
            currentClaimPrice = 10 finney * (rawNewClaimPrice / 10 finney);
        } else if (rawNewClaimPrice < 100 ether) {
            currentClaimPrice = 100 finney * (rawNewClaimPrice / 100 finney);
        } else if (rawNewClaimPrice < 1000 ether) {
            currentClaimPrice = 1 ether * (rawNewClaimPrice / 1 ether);
        } else if (rawNewClaimPrice < 10000 ether) {
            currentClaimPrice = 10 ether * (rawNewClaimPrice / 10 ether);
        } else {
            currentClaimPrice = rawNewClaimPrice;
        }

         
        ThroneClaimed(currentMonarch.etherAddress, currentMonarch.name, currentClaimPrice);
    }

     
    function sweepCommission(uint amount) onlywizard {
         
        wizardAddress.send(amount);
    }

     
    function transferOwnership(address newOwner) onlywizard {
        wizardAddress = newOwner;
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
