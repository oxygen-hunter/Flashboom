 

 
 
 
 
 

 
 
 

 
 
 
 
 

 
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

     
     

  function buyRareItem(address _player, uint256 _platValue,uint256 _rareId) internal {
    require(cards.getGameStarted());        
    address previousOwner = rare.getRareItemsOwner(_rareId);  // rare card
    require(previousOwner != 0);
    require(_player!=previousOwner);  // can not buy from itself
    
    uint256 ethCost = rare.getRareItemsPLATPrice(_rareId); // get plat cost
    uint256 totalCost = SafeMath.add(cards.coinBalanceOf(_player,1),_platValue);
    require(totalCost >= ethCost); 
    // We have to claim buyer/sellder's goo before updating their production values 
    cards.updatePlayersCoinByOut(_player);
    cards.updatePlayersCoinByOut(previousOwner);

    uint256 upgradeClass;
    uint256 unitId;
    uint256 upgradeValue;
    (,,,,upgradeClass, unitId, upgradeValue) = rare.getRarePLATInfo(_rareId);
    
    // modify weight
    cards.upgradeUnitMultipliers(_player, upgradeClass, unitId, upgradeValue); 
    cards.removeUnitMultipliers(previousOwner, upgradeClass, unitId, upgradeValue); 

    // Splitbid/Overbid
    if (ethCost > _platValue) {
      cards.setCoinBalance(_player,SafeMath.sub(ethCost,_platValue),1,false);
    } else if (_platValue > ethCost) {
      // Store overbid in their balance
      cards.setCoinBalance(_player,SafeMath.sub(_platValue,ethCost),1,true);
    }  
    // Distribute ethCost  uint256 devFund = ethCost / 50; 
    uint256 devFund = uint256(SafeMath.div(ethCost, 20)); // 5% fee on purchases (marketing, gameplay & maintenance)  抽成2%
    uint256 dividends = uint256(SafeMath.div(ethCost,20)); // 5% goes to pool 

    cards.setTotalEtherPool(dividends,1,true);  // 5% to pool
    cards.setCoinBalance(owner,devFund,1,true);  // 5% fee
        
    // Transfer / update rare item
    rare.transferToken(previousOwner,_player,_rareId); 
    rare.setRarePrice(_rareId,SafeMath.div(SafeMath.mul(rare.getRareItemsPrice(_rareId),5),4));
    
    cards.setCoinBalance(previousOwner,SafeMath.sub(ethCost,SafeMath.add(dividends,devFund)),1,true);
    
    if (cards.getUintsOwnerCount(_player)<=0) {
      cards.AddPlayers(_player);
    }
   
    cards.setUintsOwnerCount(_player,1,true);
    cards.setUintsOwnerCount(previousOwner,1,true);

    //tell the world
    BuyRareCard(_player, previousOwner, _rareId, ethCost);
  }


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
