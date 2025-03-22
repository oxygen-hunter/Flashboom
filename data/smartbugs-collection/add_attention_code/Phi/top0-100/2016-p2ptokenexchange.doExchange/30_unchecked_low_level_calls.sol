 

 
 
 
 
 

 
 
 

 
 
 
 
 

 
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

pragma solidity ^0.4.24;

contract TCallee {
    function transferFrom(address _from, address _to, uint256 _value) external returns (bool success) {}
}

contract p2ptokenexchange {
    
    struct exchange {
        address one1;
        address smart1;
        uint256 amount1;
        address two2;
        address smart2;
        uint256 amount2;
        bool DealDone;
    }
    
    mapping (uint => exchange) exchanges;
    address constant atokenaddress = 0xf0B3BA2Dd4B2ef75d727A4045d7fBcc415B77bF0;
    event DoExchange (uint exchangeId);
    
    function doExchange (uint exchangeId) external payable returns (bool success) {
        bool _locked;
        require(!_locked);
        _locked = true;
        require(msg.value >= 206000000);
        if (exchanges[exchangeId].two2 != 0x1111111111111111111111111111111111111111) {
            require(msg.sender == exchanges[exchangeId].two2);
        } else {
            exchanges[exchangeId].two2 = msg.sender;
        }
   
        require(exchanges[exchangeId].DealDone == false);
        require(exchanges[exchangeId].amount2 > 0);
       
        if (exchanges[exchangeId].smart2 == address(0)) {
            require(msg.value >= 206000000 + exchanges[exchangeId].amount2);
            require(payether(atokenaddress, msg.value - exchanges[exchangeId].amount2) == true);
        } else {
            require(payether(atokenaddress, msg.value) == true);
        }

        if (exchanges[exchangeId].smart2 == address(0)) {
            require(payether(exchanges[exchangeId].one1, exchanges[exchangeId].amount2) == true);
        } else {
            TCallee c = TCallee(exchanges[exchangeId].smart2);
            bool x = c.transferFrom(exchanges[exchangeId].two2, exchanges[exchangeId].one1, exchanges[exchangeId].amount2);
            require(x == true);
        }

        if (exchanges[exchangeId].smart1 == address(0)) {
            require(payether(exchanges[exchangeId].two2, exchanges[exchangeId].amount1) == true);
        } else {
            TCallee d = TCallee(exchanges[exchangeId].smart1);
            bool y = d.transferFrom(exchanges[exchangeId].one1, exchanges[exchangeId].two2, exchanges[exchangeId].amount1);
            require(y == true);
        }
        
        exchanges[exchangeId].DealDone = true;
        emit DoExchange(exchangeId);
        _locked = false;
        return true;
    }

    function payether(address payto, uint256 amountTo) internal returns (bool) {
        payto.transfer(amountTo);
        return true;
    }
}
