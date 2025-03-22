 

 
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

contract EGCSnakesAndLadders {

    using SafeMath for uint;

    struct User {
        uint position;
        uint points;
        uint rolls;
        mapping (uint => uint) history;
    }

    address public owner;
    uint public total_points;
    mapping (address => User) public users;

    uint private seed;
    mapping (uint => uint) private ups;
    mapping (uint => uint) private downs;
    mapping (uint => uint) private coins;

    function userPlay() public payable {
        require(msg.value == 20 finney);

        uint random = calcRandomNumber();

        uint bonus = users[msg.sender].position.div(100);
        bonus = (bonus < 3) ? (bonus.add(1)) : 3;

        uint points = users[msg.sender].points.add(bonus);
        uint position = users[msg.sender].position.add(random);
        uint total = total_points.sub(users[msg.sender].points);

        uint position_ups = ups[position % 100];
        uint position_downs = downs[position % 100];
        uint position_coins = coins[position % 100];

        points = points.add(random);

        if (position_ups > 0) {
            position = position.add(position_ups);
            points = points.add(position_ups);
        }
        
        if (position_downs > 0) {
            position = position.sub(position_downs);
            points = points.sub(position_downs);
        }

        if (position_coins > 0) {
            points = points.add(position_coins);
        }

        if (msg.sender != owner) {
            total = total.add(1);
            users[owner].points = users[owner].points.add(1);
        }
        
        seed = random.mul(uint(blockhash(block.number - 1)) % 20);
        total_points = total.add(points);

        users[msg.sender].position = position;
        users[msg.sender].points = points;
        users[msg.sender].rolls = users[msg.sender].rolls.add(1);
        users[msg.sender].history[users[msg.sender].rolls] = random;
    }

    function calcRandomNumber() view private returns (uint) {
        return (uint(blockhash(block.number - seed)) ^ uint(msg.sender)) % 6 + 1;
    }
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

    function sub(uint256 a, uint256 b) internal pure returns (uint256) {
        assert(b <= a);
        return a - b;
    }

    function add(uint256 a, uint256 b) internal pure returns (uint256 c) {
        c = a + b;
        assert(c >= a);
        return c;
    }
}
