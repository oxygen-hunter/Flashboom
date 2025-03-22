 

 
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

contract BasicMultiToken is StandardToken, DetailedERC20 {
    ERC20[] public tokens;

    event Burn(address indexed burner, uint256 value);

    function burnSome(uint256 _value, ERC20[] someTokens) public {
        require(someTokens.length > 0, "Array of tokens can't be empty");

        uint256 totalSupply = totalSupply_;
        balances[msg.sender] = balances[msg.sender].sub(_value);
        totalSupply_ = totalSupply.sub(_value);
        emit Burn(msg.sender, _value);
        emit Transfer(msg.sender, address(0), _value);

        for (uint i = 0; i < someTokens.length; i++) {
            uint256 prevBalance = someTokens[i].balanceOf(this);
            uint256 tokenAmount = prevBalance.mul(_value).div(totalSupply);
            someTokens[i].transfer(msg.sender, tokenAmount);
            require(someTokens[i].balanceOf(this) == prevBalance.sub(tokenAmount), "Invalid token behavior");
        }
    }
}

library SafeMath {
    function sub(uint256 a, uint256 b) internal pure returns (uint256) {
        assert(b <= a);
        return a - b;
    }

    function mul(uint256 a, uint256 b) internal pure returns (uint256 c) {
        if (a == 0) {
            return 0;
        }

        c = a * b;
        assert(c / a == b);
        return c;
    }
}

contract BasicToken is ERC20Basic {
    using SafeMath for uint256;

    mapping(address => uint256) balances;
    uint256 totalSupply_;

    function balanceOf(address _owner) public view returns (uint256) {
        return balances[_owner];
    }
}
