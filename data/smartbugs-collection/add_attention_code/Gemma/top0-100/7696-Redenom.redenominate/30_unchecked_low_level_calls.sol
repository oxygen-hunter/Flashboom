 

 
 
 
 
 

 
 
 

 
 
 
 
 

 
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

     
     

    function redenominate() public onlyAdmin returns(uint current_round){
        require(frozen == false); 
        require(round<9); // Round must be < 9

        // Deleting funds rest from TS
        _totalSupply = _totalSupply.sub( team_fund%mul[round] ).sub( redenom_dao_fund%mul[round] ).sub( dec[8-round]*mul[round-1] );

        // Redenominating 3 vars: _totalSupply team_fund redenom_dao_fund
        _totalSupply = ( _totalSupply / mul[round] ) * mul[round];
        team_fund = ( team_fund / mul[round] ) * mul[round]; // Redenominates team_fund
        redenom_dao_fund = ( redenom_dao_fund / mul[round] ) * mul[round]; // Redenominates redenom_dao_fund

        if(round>1){
            // decimals burned in last round and not distributed
            uint superold = dec[(8-round)+1]; 

            // Returning them to epoch_fund
            epoch_fund = epoch_fund.add(superold * mul[round-2]);
            dec[(8-round)+1] = 0;
        }

        
        if(round<8){ // if round between 1 and 7 

            uint unclimed = dec[8-round]; // total sum of burned decimal
            //[23,32,43,34,34,54,34, ->46<- ]
            uint total_current = dec[8-1-round]; // total sum of last active decimal
            //[23,32,43,34,34,54, ->34<-, 46]

            // security check
            if(total_current==0){
                current_toadd = [0,0,0,0,0,0,0,0,0]; 
                round++;
                return round;
            }

            // Counting amounts to add on every digit
            uint[9] memory numbers  =[uint(1),2,3,4,5,6,7,8,9]; // 
            uint[9] memory ke9  =[uint(0),0,0,0,0,0,0,0,0]; // 
            uint[9] memory k2e9  =[uint(0),0,0,0,0,0,0,0,0]; // 

            uint k05summ = 0;

                for (uint k = 0; k < ke9.length; k++) {
                     
                    ke9[k] = numbers[k]*1e9/total_current;
                    if(k<5) k05summ += ke9[k];
                }             
                for (uint k2 = 5; k2 < k2e9.length; k2++) {
                    k2e9[k2] = uint(ke9[k2])+uint(k05summ)*uint(weight[k2])/uint(100);
                }
                for (uint n = 5; n < current_toadd.length; n++) {
                    current_toadd[n] = k2e9[n]*unclimed/10/1e9;
                }
                // current_toadd now contains all digits
                
        }else{
            if(round==8){
                // Returns last burned decimals to epoch_fund
                epoch_fund = epoch_fund.add(dec[0] * 10000000); //1e7
                dec[0] = 0;
            }
            
        }

        round++;
        emit Redenomination(round);
        return round;
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
