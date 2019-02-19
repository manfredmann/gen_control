#include <iostream>
#include <cxxopts.hpp>
#include "gen.h"

using namespace std;

int main(int argc, char *argv[]) {
  cout << std::fixed;
  try {
    bool output_enable = false;

    cxxopts::Options options(argv[0], "Generator control tool\n(c) 2019 Roman Serov <roman@serov.co>");

    options.add_options()
        ("w,wave",  "Waveform (SIN, SQU, RAMP)",      cxxopts::value<std::string>())
        ("f,freq",  "Frequency (Hz)",                 cxxopts::value<unsigned int>())
        ("r,load",  "Load resistance (Ohm)",          cxxopts::value<unsigned int>())
        ("o,outp",  "Output enable",                  cxxopts::value<bool>(output_enable))
        ("h,help",  "Print help")
        ("debug",   "Debug");
    options.add_options("Amplitude")
        ("a,ampl",        "Amplitude (V)",                  cxxopts::value<double>())
        ("t,ampl-type",   "Amplitude type (VPP, VRMS)",     cxxopts::value<string>()->default_value("VPP"));

    auto args = options.parse(argc, argv);

    if (args.count("h")) {
      std::cout << options.help({"", "Amplitude"}) << std::endl;
      exit(0);
    }

    Generator gen;

    if (args.count("debug")) {
      gen.set_debug(true);
    }

    gen.init();
    cout << "ID:\t\t\t\t\t" << gen.get_identifier() << endl;

    gen.get_error();
    gen.send_cls();

    if (args.count("w")) {
      string              waveform_str = args["w"].as<string>();
      Waveform::Waveform  waveform(waveform_str);

      cout << "Set waveform:\t\t\t\t" << waveform.get_type_str() << " ";
      gen.set_waveform(waveform);

      cout << gen.get_error() << endl;
    }

    if (args.count("r")) {
      unsigned int load = args["r"].as<unsigned int>();
      cout << "Set load reistance:\t" << std::setw(15) << load << " Om" << " ";

      gen.set_load(int(load));
      cout << gen.get_error() << endl;
    }

    if (args.count("a")) {
      double ampl = args["a"].as<double>();
      Amplitude::Amplitude amp(ampl, args["t"].as<string>());
      cout << "Set amplitude:\t\t" << std::setw(15) << setprecision(3) << ampl << " " << amp.get_type_str() << " ";

      gen.set_amplitude(amp);
      cout << gen.get_error() << endl;
    }

    if (args.count("f")) {
      unsigned int freq = args["f"].as<unsigned int>();
      cout << "Set frequency:\t\t" << std::setw(15) << freq << " Hz" << " ";

      gen.set_frequency(freq);
      cout << gen.get_error() << endl;
    }

    if (output_enable) {
      cout << "Set output enable." << endl;
    }

    gen.set_output(output_enable);

    cout << "Current waveform.:\t\t\t"  << gen.get_waveform().get_type_str() << endl;
    cout << "Current freq.:\t\t"        << std::setw(15) << gen.get_frequency() << " Hz" << endl;
    Amplitude::Amplitude amp = gen.get_amplitude();

    cout << "Current ampl.:\t\t"        << std::setw(15) << amp.get_amplitude()  << " " << amp.get_type_str() << endl;
    cout << "Current load:\t\t"         << std::setw(15) << gen.get_load() << " Ohm" << endl;
  } catch (const cxxopts::OptionException &e) {
    cout << "error parsing options: "   << e.what() << std::endl;
    exit(1);
  } catch (USBErrors::USBException &e) {
    cout << "USB Error: "       << e.getError() << endl;
  } catch (USBErrors::USBTransferException &e) {
    cout << "USB Error: "       << e.getError() << endl;
  } catch (Waveform::WaveformException &e) {
    cout << "Waveform Error: "  << e.getError() << endl;
  } catch (Amplitude::AmplitudeException &e) {
    cout << "Amplitude Error: " << e.getError() << endl;
  }

  return 0;
}
