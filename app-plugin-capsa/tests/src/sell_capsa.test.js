import "core-js/stable";
import "regenerator-runtime/runtime";
import ledgerService from '@ledgerhq/hw-app-eth/lib/services/ledger'
import { waitForAppScreen, zemu, genericTx, nano_models,SPECULOS_ADDRESS, txFromEtherscan} from './test.fixture';
import { ethers } from "ethers";
import { parseEther, parseUnits} from "ethers/lib/utils";

// EDIT THIS: Replace with your contract address
const contractAddr = "0xef794b989190a0667a6bf25bd603422f659a9aaa";
// EDIT THIS: Replace `boilerplate` with your plugin name
const pluginName = "capsa";
const testNetwork = "polygon";
const abi_path = `../networks/${testNetwork}/${pluginName}/abis/` + contractAddr + '.json';
const abi = require(abi_path);

// Test from constructed transaction
// EDIT THIS: build your own test
nano_models.forEach(function(model) {
  test('[Nano ' + model.letter + '] Buy CAPSA', zemu(model, async (sim, eth) => {
    const contract = new ethers.Contract(contractAddr, abi);

    // Constants used to create the transaction
    // EDIT THIS: Remove what you don't need
    const amount_capsa = "1000000";
    // We set beneficiary to the default address of the emulator, so it maches sender address
    // const beneficiary = SPECULOS_ADDRESS;
  
    // EDIT THIS: adapt the signature to your method
    // signature: swapExactETHForTokens(uint amountOutMin, address[] calldata path, address to, uint deadline)
    // EDIT THIS: don't call `swapExactETHForTokens` but your own method and adapt the arguments.
    const {data} = await contract.populateTransaction.sellCAPSA(amount_capsa);
  
    // console.log(data)
  
    // Get the generic transaction template
    let unsignedTx = genericTx;
    // Modify `to` to make it interact with the contract
    unsignedTx.to = contractAddr;
    // Modify the attached data
    unsignedTx.data = data;
    // EDIT THIS: get rid of this if you don't wish to modify the `value` field.
    // Modify the number of ETH sent
    // unsignedTx.value = parseEther("0.1");
  
    // Create serializedTx and remove the "0x" prefix
    const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);
    // const rawTx = "0x02f89281894185073a20cca485073a20d1528301c49894ef794b989190a0667a6bf25bd603422f659a9aaa80a41a674419000000000000000000000000000000000000000000000000000000012a05f200c001a03207d1f25293ad99678edc7b8c2b9a0e3ced921c2f198942b1f6c3aedac6b6d0a04a049a2ae90b98e78d8b4270e5a8d00dcd4c82da7432a17cdb6b402ad040ea2a";
    // const resolution = ledgerService.resolveTransaction(rawTx);
    // const serializedTx = txFromEtherscan(rawTx);
  
    const tx = eth.signTransaction(
      "44'/60'/0'/0",
      serializedTx,
    );
  
    const right_clicks = model.letter === 'S' ? 7 : 5;
  
    // Wait for the application to actually load and parse the transaction
    await waitForAppScreen(sim);
    // Navigate the display by pressing the right button 10 times, then pressing both buttons to accept the transaction.
    // EDIT THIS: modify `10` to fix the number of screens you are expecting to navigate through.
    await sim.navigateAndCompareSnapshots('.', model.name + '_sell_capsa', [right_clicks, 0]);
  
    await tx;
  }));
});

